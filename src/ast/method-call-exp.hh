/**
 ** \file ast/method-call-exp.hh
 ** \brief Declaration of ast::MethodCallExp.
 */

#ifndef AST_METHOD_CALL_EXP_HH
# define AST_METHOD_CALL_EXP_HH

# include <ast/call-exp.hh>
# include <ast/var.hh>
# include <ast/method-dec.hh>

namespace ast
{

  /** \class ast::MethodCallExp
   ** \brief Method call.
   **
   ** A method call is \em not a function call in the strict sense
   ** of object-oriented programming.  Inheritance is used as a
   ** factoring tool here.
   */

  class MethodCallExp : public CallExp
  {
  // FIXME: Some code was deleted here.
  };

} // namespace ast

# include <ast/method-call-exp.hxx>

#endif // !AST_METHOD_CALL_EXP_HH
