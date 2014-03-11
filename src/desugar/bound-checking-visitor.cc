/**
 ** \file desugar/bound-checking-visitor.cc
 ** \brief Implementation of desugar::BoundCheckingVisitor.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <parse/libparse.hh>
#include <desugar/bound-checking-visitor.hh>
#include <misc/symbol.hh>

namespace desugar
{
  namespace
  {
    /// Return the name of the boxed type for \a s.
    std::string
    box(const misc::symbol& s)
    {
      return "_box_" + s.name_get();
    }
  }

  BoundCheckingVisitor::BoundCheckingVisitor()
    : super_type()
  {
  }

  BoundCheckingVisitor::~BoundCheckingVisitor()
  {
  }


  /*-----------------------.
  | Array bound checking.  |
  `-----------------------*/

  // FIXME: Some code was deleted here.

} // namespace desugar
