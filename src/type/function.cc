/**
 ** \file type/function.cc
 ** \brief Implementation for type/function.hh.
 */

#include <ostream>

#include <type/function.hh>
#include <type/visitor.hh>

namespace type
{

  void
  Function::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Function::accept(Visitor& v)
  {
    v(*this);
  }

  // FIXME: Some code was deleted here.

} // namespace type
