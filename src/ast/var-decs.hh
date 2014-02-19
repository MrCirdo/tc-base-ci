/**
 ** \file ast/var-decs.hh
 ** \brief Declaration of ast::VarDecs.
 */

#ifndef AST_VAR_DECS_HH
# define AST_VAR_DECS_HH

# include <list>

# include <ast/any-decs.hh>
# include <ast/var-dec.hh>

namespace ast
{
  /// Define shorthand type for Variable declarations.
  typedef AnyDecs<VarDec> VarDecs;

} // namespace ast

#endif // !AST_VAR_DECS_HH
