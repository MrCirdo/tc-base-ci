/**
 ** \file canon/canon.hh
 ** \brief Declaration canon::Canon.
 */

#pragma once

#include <tree/fwd.hh>

namespace canon
{

  /// Object function to canonicalize tree::Tree code.
  class Canon
  {
  public:
    /// Build a canonizer.
    Canon(bool trace_p = false);

    /// Canonicalizing Eseq and Calls.
    tree::rStm operator()(const tree::rStm& tree);

  private:
    /// The actual worker.
    tree::rTree canon(tree::rTree tree);

    /** \brief Are there any ESEQ in [\a begin, \a end) such that \a a does
        not commute with its SEQ part?
        Iff there are, return FALSE.  */
    bool commutes_with_all_eseq(const tree::rTree& a,
                                tree::tree_list_type::iterator start,
                                tree::tree_list_type::iterator end);


    /*------------------.
    | Rewriting rules.  |
    `------------------*/

    /// Assemble statements \a s1 and \a s2 together.
    tree::rStm assemble_stm(const tree::rStm& s1, const tree::rStm& s2);

    /// Assemble statement \a s and expression \a e together.
    tree::rExp assemble_eseq(tree::rStm s, tree::rExp e);

    /** \brief Canonicalize \a seq, in particular, bubble up the sub SEQ,
        and get rid of nops..  */
    tree::rSeq operator()(const tree::rSeq& seq);

    /// Canonicalize \a eseq.
    tree::rExp operator()(const tree::rEseq& eseq);

    /// Is \a call a (LIR-)valid son of \a tree?
    bool valid_call(const tree::rTree& tree, const tree::rTree& call);

    /// Canonicalize \a tree: lift the ESEQ children higher.
    tree::rTree canon_default(const tree::rTree& tree);


    /*-------------.
    | Attributes.  |
    `-------------*/
  private:
    /// Report debugging information.
    bool trace_p_;
  };
}
