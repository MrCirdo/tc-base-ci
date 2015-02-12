/**
 ** \file ast/decs-list.hxx
 ** \brief Inline methods of ast::DecsList.
 */

#ifndef AST_DECS_LIST_HXX
# define AST_DECS_LIST_HXX

# include <ast/decs-list.hh>

namespace ast
{


  inline const DecsList::decs_type&
  DecsList::decs_get() const
  {
    return decs_;
  }
  inline DecsList::decs_type&
  DecsList::decs_get()
  {
    return decs_;
  }


} // namespace ast

#endif // !AST_DECS_LIST_HXX
