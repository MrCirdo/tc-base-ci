/**
 ** \file tree/seq.cc
 ** \brief Implementation for tree/seq.hh.
 **/

#include <ostream>

#include <misc/indent.hh>
#include <tree/seq.hh>
#include <tree/trees.hh>

namespace tree
{

  std::ostream&
  Seq::tag_print(std::ostream&) const
  {
    unreachable();
  }

  std::ostream&
  Seq::dump(std::ostream& ostr) const
  {
    return ostr << "seq"
                << misc::incendl
                << children_get()
                << misc::decendl
                << "seq end";
  }

  Tree::kind_tree_type
  Seq::kind_get() const
  {
    return seq_kind;
  }

}
