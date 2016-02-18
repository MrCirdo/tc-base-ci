/**
 ** \file ast/metavar-exp.hh
 ** \brief Declaration of ast::MetavarExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/metavariable.hh>

namespace ast
{

  /// MetavarExp.
  class MetavarExp : public Exp, public Metavariable
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a MetavarExp node.
    MetavarExp(const Location& location, unsigned id);
    /// Destroy a MetavarExp node.
    virtual ~MetavarExp();
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

#include <ast/metavar-exp.hxx>

