/**
 ** \file ast/var.hh
 ** \brief Declaration of ast::Var.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  /// Var.
  class Var : public Exp
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Var node.
    Var(const Location& location);
    /// Destroy a Var node.
    virtual ~Var();
    /** \} */
  };

} // namespace ast

#include <ast/var.hxx>

