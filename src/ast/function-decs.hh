/**
 ** \file ast/function-decs.hh
 ** \brief Declaration of ast::FunctionDecs.
 */

#ifndef AST_FUNCTION_DECS_HH
# define AST_FUNCTION_DECS_HH

# include <list>

# include <ast/any-decs.hh>
# include <ast/function-dec.hh>

namespace ast
{
  /// Define shorthand type for Function declarations.
  typedef AnyDecs<FunctionDec> FunctionDecs;

} // namespace ast

#endif // !AST_FUNCTION_DECS_HH
