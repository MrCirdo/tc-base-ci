/**
 ** \file tree/eseq.hxx
 ** \brief Inline methods for tree/eseq.hh.
 **/

#ifndef TREE_ESEQ_HXX
# define TREE_ESEQ_HXX

# include <tree/eseq.hh>

namespace tree
{

  inline
  Eseq::Eseq(const rStm& stm, const rExp& exp)
    : Exp()
  {
    child_push_back(stm);
    child_push_back(exp);
  }

  inline rStm
  Eseq::stm_get() const
  {
    return child_get(0).cast<Stm>();
  }

  inline rExp
  Eseq::exp_get() const
  {
    return child_get(1).cast<Exp>();
  }

}

#endif // !TREE_ESEQ_HXX
