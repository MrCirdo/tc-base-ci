/**
 ** \file ast/class-ty.hh
 ** \brief Declaration of ast::ClassTy.
 */

#ifndef AST_CLASS_TY_HH
# define AST_CLASS_TY_HH

# include <ast/name-ty.hh>
# include <ast/ty.hh>
# include <ast/decs-list.hh>

namespace ast
{

  /// ClassTy.
  class ClassTy : public Ty
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a ClassTy node.
    ClassTy(const Location& location, NameTy* super, DecsList* decs);
    /// Destroy a ClassTy node.
    virtual ~ClassTy();
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
    /// Return super class.
    const NameTy& super_get() const;
    /// Return super class.
    NameTy& super_get();
    /// Return list of declarations.
    const DecsList& decs_get() const;
    /// Return list of declarations.
    DecsList& decs_get();
    /** \} */

  protected:
    /// Super class.
    NameTy* super_;
    /// List of declarations.
    DecsList* decs_;
  };

} // namespace ast

# include <ast/class-ty.hxx>

#endif // !AST_CLASS_TY_HH
