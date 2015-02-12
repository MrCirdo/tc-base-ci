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
  {}

  template <template <typename> class Const>
  GenObjectVisitor<Const>::~GenObjectVisitor()
  {}


  /*-------------------------------.
  | Object-related visit methods.  |
  `-------------------------------*/

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(typename Const<ClassTy>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(typename Const<MethodDecs>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(typename Const<MethodDec>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(typename Const<MethodCallExp>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(typename Const<ObjectExp>::type& e)
  {
  // FIXME: Some code was deleted here.
  }


} // namespace ast

#endif // !AST_OBJECT_VISITOR_HXX
