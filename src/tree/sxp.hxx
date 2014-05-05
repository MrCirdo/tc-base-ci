/**
 ** \file tree/sxp.hxx
 ** \brief Inline methods for tree/sxp.hh.
 **/

#ifndef TREE_SXP_HXX
# define TREE_SXP_HXX

# include <tree/sxp.hh>

namespace tree
{

  inline
  Sxp::Sxp(const rExp& exp)
    : Stm()
  {
    child_push_back(exp);
  }

  inline rExp
  Sxp::exp_get() const
  {
    return child_get(0).cast<Exp>();
  }

}

#endif // !TREE_SXP_HXX
