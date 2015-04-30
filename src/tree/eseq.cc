/**
 ** \file tree/eseq.cc
 ** \brief Implementation for tree/eseq.hh.
 **/

#include <ostream>

#include <misc/indent.hh>
#include <tree/eseq.hh>

namespace tree
{

  std::ostream&
  Eseq::tag_print(std::ostream&) const
  {
    unreached();
  }


  std::ostream&
  Eseq::dump(std::ostream& ostr) const
  {
    ostr << "eseq";
    // If the stm is a seq, don't increment again.
    if (stm_get().is_a<Seq>())
      ostr << misc::iendl
           << *stm_get()
           << misc::incendl;
    else
      ostr << misc::incendl
           << *stm_get()
           << misc::iendl;
    return ostr << *exp_get() << misc::decindent;
  }

  Tree::kind_tree_type
  Eseq::kind_get() const
  {
    return eseq_kind;
  }

}
