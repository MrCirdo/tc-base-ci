/**
 ** \file canon/canon.cc
 ** \brief Canonicalizing HIR into LIR.
 */

#include <iostream>

#include <canon/canon.hh>
#include <misc/indent.hh>
#include <misc/vector.hh>
#include <temp/temp.hh>
#include <tree/all.hh>

namespace canon
{
  Canon::Canon(bool trace_p)
    : trace_p_(trace_p)
  {}

  /// Canonicalizing Eseq and Calls.
  tree::rStm Canon::operator()(const tree::rStm& tree)
  {
    // 1. Canonicalize.
    if (trace_p_)
      std::cerr << "canon: Input: " << &*tree << misc::incendl << *tree
                << misc::iendl;

    tree::rStm res = canon(tree).cast<tree::Stm>();

    // The rest of the compiler expects a Seq.
    if (!res.is_a<tree::Seq>())
      res = new tree::Seq(res);

    if (trace_p_)
      std::cerr << "canon: Result: " << &*res << misc::incendl << *res
                << misc::decindent << misc::decendl;

    return res;
  }

  /*----------------------.
  | Auxiliary functions.  |
  `----------------------*/

  /// \brief Return false if \a tree has to be run.
  /// Try to say true as much as possible.
  struct is_nop
  {
    bool operator()(const tree::rTree& tree)
    {
  // FIXME: Some code was deleted here.
    }
  };

  /** \brief Return false if \a a and \a b cannot be swapped, try to
      say true as much as possible.

      Note that we are not trying to understand whether it is valid to
      swap \a a and \a b rather, we are checking if \a a can influence the
      meaning of \a b (or vice versa), in which case we must not permute
      them.  It is up to the caller to make proper use of this
      information.

      For instance in `BINOP(-, A, B)', if A and B are constants, the
      caller should not swap them, nevertheless this function shall
      return true.  */
  struct commute_p
  {
    commute_p(bool trace)
      : trace_(trace)
    {}

    bool commute_p_(const tree::rTree& a, const tree::rTree& b)
    {
  // FIXME: Some code was deleted here.
    }

    bool operator()(const tree::rTree& a, const tree::rTree& b)
    {
  // FIXME: Some code was deleted here.
    }

    bool trace_;
  };

  bool Canon::commutes_with_all_eseq(const tree::rTree& a,
                                     tree::tree_list_type::iterator begin,
                                     tree::tree_list_type::iterator end)
  {
    commute_p commutes(trace_p_);
    return std::all_of(begin, end, [&](const tree::rTree& tree) {
      if (auto eseq = tree.unsafe_cast<tree::Eseq>())
        return commutes(a, eseq->stm_get());
      return true;
    });
  }

  // ----------------- //
  // Rewriting rules.  //
  // ----------------- //

  tree::rStm Canon::assemble_stm(const tree::rStm& s1, const tree::rStm& s2)
  {
    if (!s1 || is_nop()(s1))
      return s2;
    if (!s2 || is_nop()(s2))
      return s1;

    tree::rSeq res = new tree::Seq;

    if (s1.is_a<tree::Seq>())
      append_and_move(res->children_get(), s1->children_get());
    else
      res->child_emplace_back(s1);

    if (s2.is_a<tree::Seq>())
      append_and_move(res->children_get(), s2->children_get());
    else
      res->child_emplace_back(s2);

    return res;
  }

  tree::rExp Canon::assemble_eseq(tree::rStm s, tree::rExp e)
  {
    if (!s || is_nop()(s))
      return e;

    if (e.is_a<tree::Eseq>())
      {
        tree::rEseq eseq = e.cast<tree::Eseq>();
        s = assemble_stm(s, eseq->stm_get());
        e = eseq->exp_get();
      }
    return new tree::Eseq(s, e);
  }

  tree::rSeq Canon::operator()(const tree::rSeq& seq)
  {
    tree::tree_list_type res;
    tree::tree_list_type& children = seq->children_get();

    if (trace_p_)
      std::cerr << "canon() seq in:" << misc::incendl << *seq << misc::decendl;

    for (tree::rTree& t : children)
      {
        if (t.is_a<tree::Seq>())
          {
            tree::rSeq subseq = t.cast<tree::Seq>();
            append_and_move(res, subseq->children_get());
          }
        else if (!is_nop()(t))
          res.emplace_back(t);
      }
    children = res;

    if (trace_p_)
      std::cerr << "canon() seq out:" << misc::incendl << *seq << misc::decendl;
    return seq;
  }

  tree::rExp Canon::operator()(const tree::rEseq& eseq)
  {
    return assemble_eseq(eseq->stm_get(), eseq->exp_get());
  }

  /** Valid CALLs are:

  SXP(CALL ...)

  MOVE(TEMP, CALL ...) */
  bool Canon::valid_call(const tree::rTree& tree, const tree::rTree& call)
  {
    if (tree.is_a<tree::Sxp>())
      return true;

    tree::rMove move = tree.unsafe_cast<tree::Move>();
    if (!move)
      return false;

    if (!move->dst_get().is_a<tree::Temp>())
      return false;

    if (call != move->src_get())
      return false;

    return true;
  }

  /** Canonicalize \a tree: lift the ESEQ children higher.

  \a tree is not an ESEQ nor a SEQ.
  Pay attention to the case of CALL too.

  The logic here is different from that of Appel.  He suggests that
  when we find an eseq, we should move its statement backwards, and
  pay attention to the conflicts with expressions that don't
  commute with this statement, in which case we need to store the
  value of this expression in a temporary, and move this move.

  This is probably very natural in a recursive implementation, but
  we are based on vectors, and this is awkward.

  The implementation below has a different viewpoint: for instance
  with `call(name f, e1, eseq(s1, e2))', we don't wait to study
  `eseq(s1, e2)' to realize that `e1' has to move: when we study
  `e1' we look whether it commutes with any eseq-statement (here
  `s1') that follow it, and if not, we immediately move it.  As a
  consequence, when we reach an eseq-statement (again, `s1'), there
  is nothing magical to do: just move it.  */

  tree::rTree Canon::canon_default(const tree::rTree& tree)
  {
    precondition(!tree.is_a<tree::Eseq>());
    precondition(!tree.is_a<tree::Seq>());

    tree::rStm bigseq;

    tree::tree_list_type& children = tree->children_get();
    tree::tree_list_type::iterator ichild;
    for (ichild = children.begin(); ichild != children.end(); ++ichild)
      {
        /* First, handle the ESEQ case, since we may have

        CALL(foo, ESEQ(..., CALL(bar)))

        in which case ESEQ elimination will bring us to...

        ESEQ(..., CALL(foo, CALL(bar)))

        which exhibits the inner CALL for the following treatment. */
        if (ichild->is_a<tree::Eseq>())
          {
            // We have a tree::Eseq, we want to move it up.
  // FIXME: Some code was deleted here.
          }

        if (ichild->is_a<tree::Call>() && !valid_call(tree, *ichild))
          {
            temp::Temp temp;
            bigseq = assemble_stm(
              bigseq,
              new tree::Move(new tree::Temp(temp), ichild->cast<tree::Call>()));
            *ichild = new tree::Temp(temp);
          }

        /* If there are ESEQ afterwards whose SEQ does not commute
           with ICHILD, we have to save the current value of ICHILD so
           that when the SEQ part of the ESEQ will be moved, the
           values are kept.

           There are two exceptions:

           1. if ICHILD is a TEMP in `MOVE(TEMP, ...)', because in
           this case, `saving' this TEMP makes no sense: it is being
           defined here, not used.

           2. if ICHILD is a MEM in `MOVE(MEM foo, ...)', in which
           case the child is foo, not the MEM!  Otherwise you would
           transform

           MOVE(MEM foo, x)

           into the incorrect

           MOVE(TEMP t, MEM(foo))
           MOVE(TEMP t, x)

           instead of the correct

           MOVE(TEMP t, foo)
           MOVE(MEM(TEMP t), x)
        */
        if (tree.is_a<tree::Move>() && ichild == children.begin())
          {
            // Nothing to do for MOVE(TEMP, ...)
            if (ichild->is_a<tree::Mem>())
              {
  // FIXME: Some code was deleted here.
              }
          }
        else
          {
  // FIXME: Some code was deleted here.
          }
      }

    if (tree.is_a<tree::Exp>())
      return assemble_eseq(bigseq, tree.cast<tree::Exp>());
    else
      return assemble_stm(bigseq, tree.cast<tree::Stm>());
  }

  tree::rTree Canon::canon(tree::rTree tree)
  {
    if (trace_p_)
      std::cerr << "canon: Studying: " << &*tree << misc::incendl << *tree
                << misc::iendl;

    // Handle the children first.
    tree::tree_list_type& children = tree->children_get();
    for (tree::rTree& t : children)
      t = canon(t);

    // Then specialize.
    if (tree.is_a<tree::Eseq>())
      tree = operator()(tree.cast<tree::Eseq>());
    else if (tree.is_a<tree::Seq>())
      tree = operator()(tree.cast<tree::Seq>());
    else
      tree = canon_default(tree);

    if (trace_p_)
      std::cerr << "canon: Result: " << &*tree << misc::incendl << *tree
                << misc::decindent << misc::decendl;
    return tree;
  }

} // namespace canon
