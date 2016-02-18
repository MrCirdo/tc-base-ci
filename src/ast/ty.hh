/**
 ** \file ast/ty.hh
 ** \brief Declaration of ast::Ty.
 */

#pragma once

#include <ast/ast.hh>

namespace ast
{

  /// Ty.
  class Ty : public Ast
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Ty node.
    Ty(const Location& location);
    /// Destroy a Ty node.
    virtual ~Ty();
    /** \} */
  };

} // namespace ast

#include <ast/ty.hxx>

