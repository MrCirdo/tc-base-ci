/**
 ** \file ast/rule-decs.hh
 ** \brief Declaration of ast::RuleDecs.
 */

#ifndef AST_RULE_DECS_HH
# define AST_RULE_DECS_HH

# include <list>

# include <ast/any-decs.hh>
# include <ast/rule-dec.hh>

namespace ast
{
  /// Define shorthand type for Rule declarations.
  typedef AnyDecs<RuleDec> RuleDecs;

} // namespace ast

#endif // !AST_RULE_DECS_HH
