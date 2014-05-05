/**
 ** \file tree/seq.hxx
 ** \brief Inline methods for tree/seq.hh.
 **/

#ifndef TREE_SEQ_HXX
# define TREE_SEQ_HXX

# include <tree/seq.hh>

namespace tree
{

  inline
  Seq::Seq (const tree_list_type& children)
    : Stm (children)
  {
  }

  inline
  Seq::Seq (const rStm& left, const rStm& right)
    : Stm ()
  {
    push_back (left);
    push_back (right);
  }

  inline
  Seq::Seq (const rStm& left)
    : Stm ()
  {
    push_back (left);
  }

  inline
  Seq::Seq (std::initializer_list<rStm> l)
    : Stm ()
  {
    for (const rStm& p : l)
      push_back (p);
  }

  inline void
  Seq::push_back (const rStm& stm)
  {
    child_push_back (stm);
  }

}

#endif // !TREE_SEQ_HXX
