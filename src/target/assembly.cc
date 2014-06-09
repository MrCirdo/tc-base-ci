/**
 ** \file target/assembly.cc
 ** \brief Implementation of target::Assembly.
 */

#include <temp/label.hh>
#include <target/assembly.hh>

namespace target
{

  Assembly::Assembly(assem::Layout& layout)
    : layout_(layout)
  {
  }

  Assembly::~Assembly()
  {
  }

  assem::Layout&
  Assembly::layout_get()
  {
    return layout_;
  }

} // namespace target
