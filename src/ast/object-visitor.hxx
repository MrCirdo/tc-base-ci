/**
 ** \file ast/object-visitor.hxx
 ** \brief Implementation for ast/object-visitor.hh.
 */

#ifndef AST_OBJECT_VISITOR_HXX
# define AST_OBJECT_VISITOR_HXX

# include <misc/contract.hh>
# include <ast/all.hh>
# include <ast/object-visitor.hh>

namespace ast
{

  template <template <typename> class Const>
  GenObjectVisitor<Const>::GenObjectVisitor()
    : GenVisitor<Const>()
  {
  }

  template <template <typename> class Const>
  GenObjectVisitor<Const>::~GenObjectVisitor()
  {
  }


  /*-------------------------------.
  | Object-related visit methods.  |
  `-------------------------------*/

  // FIXME: Some code was deleted here (Required at TC-3).

} // namespace ast

#endif // !AST_OBJECT_VISITOR_HXX
