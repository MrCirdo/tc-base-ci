/**
 ** \file ast/cast-exp.hh
 ** \brief Declaration of ast::CastExp.
 */

#ifndef AST_CAST_EXP_HH
# define AST_CAST_EXP_HH

# include <ast/exp.hh>
# include <ast/ty.hh>

namespace ast
{


  /** \class ast::CastExp
   ** \brief Cast the type of an expression to a given type.
   **
   ** This node is only used in the bound checking transformation
   ** (see desugar::bound_checks_add).  You don't need to worry
   ** about it (nor about the `cast' keyword) if you don't implement
   ** this option.
   */

  class CastExp : public Exp
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a CastExp node.
    CastExp(const Location& location, Exp* exp, Ty* ty);
    /// Destroy a CastExp node.
    virtual ~CastExp();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
  public:
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
  public:
    /// Return the cast expression.
    const Exp& exp_get() const;
    /// Return the cast expression.
    Exp& exp_get();
    /// Return the target type.
    const Ty& ty_get() const;
    /// Return the target type.
    Ty& ty_get();
    /** \} */

  protected:
    /// The cast expression.
    Exp* exp_;
    /// The target type.
    Ty* ty_;
  };

} // namespace ast

# include <ast/cast-exp.hxx>

#endif // !AST_CAST_EXP_HH
