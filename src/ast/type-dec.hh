/**
 ** \file ast/type-dec.hh
 ** \brief Declaration of ast::TypeDec.
 */

#ifndef AST_TYPE_DEC_HH
# define AST_TYPE_DEC_HH

# include <ast/type-constructor.hh>
# include <ast/dec.hh>
# include <ast/ty.hh>

namespace ast
{

  /// TypeDec.
  class TypeDec : public Dec, public TypeConstructor
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a TypeDec node.
    TypeDec(const Location& location, const misc::symbol& name, Ty* ty);
    /// Destroy a TypeDec node.
    virtual ~TypeDec();
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
    /// Return type definition.
    const Ty& ty_get() const;
    /// Return type definition.
    Ty& ty_get();
    /** \} */

  protected:
    /// Type definition.
    Ty* ty_;
  };

} // namespace ast

# include <ast/type-dec.hxx>

#endif // !AST_TYPE_DEC_HH
