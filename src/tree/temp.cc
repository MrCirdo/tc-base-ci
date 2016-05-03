/**
 ** \file tree/temp.cc
 ** \brief Implementation for tree/temp.hh.
 **/

#include <temp/temp.hh>
#include <tree/temp.hh>

namespace tree
{
  std::ostream&
  Temp::tag_print(std::ostream& ostr) const
  {
    return ostr << "temp " << temp_;
  }

  Tree::kind_tree_type
  Temp::kind_get() const
  {
    return temp_kind;
  }
}

