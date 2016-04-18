/**
 ** \file ast/nil-exp.hh
 ** \brief Declaration of ast::NilExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/type-constructor.hh>

namespace ast
{

  /// NilExp.
  class NilExp : public Exp, public TypeConstructor
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a NilExp node.
    NilExp(const Location& location);
    /// Destroy a NilExp node.
    virtual ~NilExp();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
  public:
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) override;
    /// \}
  };

} // namespace ast

#include <ast/nil-exp.hxx>

