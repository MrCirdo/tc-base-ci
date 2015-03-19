/**
 ** \file ast/field-init.hh
 ** \brief Declaration of ast::FieldInit.
 */

#ifndef AST_FIELD_INIT_HH
# define AST_FIELD_INIT_HH

# include <ast/ast.hh>
# include <ast/exp.hh>
# include <misc/symbol.hh>

namespace ast
{

  /// FieldInit.
  class FieldInit : public Ast
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a FieldInit node.
    FieldInit(const Location& location, const misc::symbol& name,
              Exp* init);
    /// Destroy a FieldInit node.
    virtual ~FieldInit();
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
    /// Return name of the field.
    const misc::symbol& name_get() const;
    /// Set name of the field.
    void name_set(const misc::symbol&);
    /// Return initial value of the field.
    const Exp& init_get() const;
    /// Return initial value of the field.
    Exp& init_get();
    /** \} */

  protected:
    /// Name of the field.
    misc::symbol name_;
    /// Initial value of the field.
    Exp* init_;
  };

} // namespace ast

# include <ast/field-init.hxx>

#endif // !AST_FIELD_INIT_HH
