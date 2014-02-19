/**
 ** \file ast/type-decs.hh
 ** \brief Declaration of ast::TypeDecs.
 */

#ifndef AST_TYPE_DECS_HH
# define AST_TYPE_DECS_HH

# include <list>

# include <ast/any-decs.hh>
# include <ast/type-dec.hh>

namespace ast
{
  /// Define shorthand type for Type declarations.
  typedef AnyDecs<TypeDec> TypeDecs;

} // namespace ast

#endif // !AST_TYPE_DECS_HH
