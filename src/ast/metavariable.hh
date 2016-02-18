/**
 ** \file ast/metavariable.hh
 ** \brief Declaration of ast::Metavariable.
 */

#pragma once


namespace ast
{

  /// Metavariable.
  class Metavariable
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Metavariable node.
    Metavariable(unsigned id);
    /// Destroy a Metavariable node.
    virtual ~Metavariable();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
  public:
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const = 0;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) = 0;
    /// \}

    /** \name Accessors.
     ** \{ */
  public:
    /// Return id of the metavariable.
    unsigned id_get() const;
    /** \} */

  protected:
    /// Id of the metavariable.
    unsigned id_;
  };

} // namespace ast

#include <ast/metavariable.hxx>

