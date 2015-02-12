/**
 ** \file ast/metavariable.hxx
 ** \brief Inline methods of ast::Metavariable.
 */

#ifndef AST_METAVARIABLE_HXX
# define AST_METAVARIABLE_HXX

# include <ast/metavariable.hh>

namespace ast
{

  inline unsigned
  Metavariable::id_get() const
  {
    return id_;
  }


} // namespace ast

#endif // !AST_METAVARIABLE_HXX
