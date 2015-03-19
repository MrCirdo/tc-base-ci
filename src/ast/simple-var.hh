/**
 ** \file ast/simple-var.hh
 ** \brief Declaration of ast::SimpleVar.
 */

#ifndef AST_SIMPLE_VAR_HH
# define AST_SIMPLE_VAR_HH

# include <ast/var-dec.hh>
# include <ast/var.hh>
# include <misc/symbol.hh>

namespace ast
{

  /// SimpleVar.
  class SimpleVar : public Var
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a SimpleVar node.
    SimpleVar(const Location& location, const misc::symbol& name);
    /// Destroy a SimpleVar node.
    virtual ~SimpleVar();
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
    /// Return variable's name.
    const misc::symbol& name_get() const;
    /// Set variable's name.
    void name_set(const misc::symbol&);
    /// Return definition site.
    const VarDec* def_get() const;
    /// Return definition site.
    VarDec* def_get();
    /// Set definition site.
    void def_set(VarDec*);
    /** \} */

  protected:
    /// Variable's name.
    misc::symbol name_;
    /// Definition site.
    VarDec* def_ = nullptr;
  };

} // namespace ast

# include <ast/simple-var.hxx>

#endif // !AST_SIMPLE_VAR_HH
