/**
 ** \file tree/sxp.cc
 ** \brief Implementation for tree/sxp.hh.
 **/

#include <ostream>

#include <tree/sxp.hh>

namespace tree
{

  std::ostream&
  Sxp::tag_print(std::ostream& ostr) const
  {
    return ostr << "sxp";
  }

  Tree::kind_tree_type
  Sxp::kind_get() const
  {
    return sxp_kind;
  }

}
