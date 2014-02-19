/**
 ** \file ast/ty.cc
 ** \brief Implementation of ast::Ty.
 */

#include <ast/visitor.hh>
#include <ast/ty.hh>

namespace ast
{

  Ty::Ty(const Location& location)
    : Ast(location)
  {}

  Ty::~Ty()
  {
  }


} // namespace ast

