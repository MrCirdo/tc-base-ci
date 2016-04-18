/**
 ** \file ast/ty.hh
 ** \brief Declaration of ast::Ty.
 */

#pragma once

#include <ast/ast.hh>
#include <ast/typable.hh>
#include <ast/type-constructor.hh>

namespace ast
{

  /// Ty.
  class Ty : public Ast, public Typable, public TypeConstructor
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Ty node.
    Ty(const Location& location);
    /// Destroy a Ty node.
    virtual ~Ty();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
  public:
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const override = 0;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) override = 0;
    /// \}
  };

} // namespace ast

#include <ast/ty.hxx>

