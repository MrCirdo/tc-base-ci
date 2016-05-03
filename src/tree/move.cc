/**
 ** \file tree/move.cc
 ** \brief Implementation for tree/move.hh.
 **/

#include <ostream>

#include <tree/move.hh>

namespace tree
{

  std::ostream&
  Move::tag_print(std::ostream& ostr) const
  {
    return ostr << "move";
  }

  Tree::kind_tree_type
  Move::kind_get() const
  {
    return move_kind;
  }

}
