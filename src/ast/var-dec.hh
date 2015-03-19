/**
 ** \file ast/var-dec.hh
 ** \brief Declaration of ast::VarDec.
 */

#ifndef AST_VAR_DEC_HH
# define AST_VAR_DEC_HH

# include <ast/dec.hh>
# include <ast/escapable.hh>
# include <ast/exp.hh>
# include <ast/name-ty.hh>

namespace ast
{

  /// VarDec.
  class VarDec : public Dec, public Escapable
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a VarDec node.
    VarDec(const Location& location, const misc::symbol& name,
           NameTy* type_name, Exp* init);
    /// Destroy a VarDec node.
    virtual ~VarDec();
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
    /// Return optional type of the declared variable.
    const NameTy* type_name_get() const;
    /// Return optional type of the declared variable.
    NameTy* type_name_get();
    /// Return the initial value (expression) assigned to the variable.
    const Exp* init_get() const;
    /// Return the initial value (expression) assigned to the variable.
    Exp* init_get();
    /** \} */

  protected:
    /// Optional type of the declared variable.
    NameTy* type_name_;
    /// The initial value (expression) assigned to the variable.
    Exp* init_;
  };

} // namespace ast

# include <ast/var-dec.hxx>

#endif // !AST_VAR_DEC_HH
