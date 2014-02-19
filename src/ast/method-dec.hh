/**
 ** \file ast/method-dec.hh
 ** \brief Declaration of ast::MethodDec.
 */

#ifndef AST_METHOD_DEC_HH
# define AST_METHOD_DEC_HH

# include <ast/function-dec.hh>

namespace ast
{

  /** \class ast::MethodDec
   ** \brief Method declaration.
   **
   ** A method declaration is \em not a function in the strict
   ** sense of object-oriented programming.  Inheritance is used
   ** as a factoring tool here.
   */

  class MethodDec : public FunctionDec
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a MethodDec node.
    MethodDec(const Location& location, const misc::symbol& name,
              VarDecs* formals, NameTy* result, Exp* body);
    /// Destroy a MethodDec node.
    virtual ~MethodDec();
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

# include <ast/method-dec.hxx>

#endif // !AST_METHOD_DEC_HH
