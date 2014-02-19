/**
 ** \file ast/method-decs.hh
 ** \brief Declaration of ast::MethodDecs.
 */

#ifndef AST_METHOD_DECS_HH
# define AST_METHOD_DECS_HH

# include <list>

# include <ast/any-decs.hh>
# include <ast/method-dec.hh>

namespace ast
{
  /// Define shorthand type for Method declarations.
  typedef AnyDecs<MethodDec> MethodDecs;

} // namespace ast

#endif // !AST_METHOD_DECS_HH
