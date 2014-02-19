/**
 ** \file ast/decs.hxx
 ** \brief Inline methods for ast/decs.hh
 */

#ifndef AST_DECS_HXX
# define AST_DECS_HXX

# include <ast/decs.hh>

namespace ast
{

  inline
  Decs::Decs(const Location& location):
    Ast(location)
  {}

} // namespace ast

#endif // !AST_DECS_HXX
