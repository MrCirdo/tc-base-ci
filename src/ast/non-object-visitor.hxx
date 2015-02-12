/**
 ** \file ast/non-object-visitor.hxx
 ** \brief Implementation for ast/non-object-visitor.hh.
 */

#ifndef AST_NON_OBJECT_VISITOR_HXX
# define AST_NON_OBJECT_VISITOR_HXX

# include <misc/contract.hh>
# include <ast/all.hh>
# include <ast/non-object-visitor.hh>

namespace ast
{

  template <template <typename> class Const>
  GenNonObjectVisitor<Const>::GenNonObjectVisitor()
    : GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenNonObjectVisitor<Const>::~GenNonObjectVisitor()
  {}


  /*-----------------------------------------.
  | Object-related visit methods, disabled.  |
  `-----------------------------------------*/

  template <template <typename> class Const>
  void
  GenNonObjectVisitor<Const>::operator()(typename Const<ClassTy>::type&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreached();
  }

  template <template <typename> class Const>
  void
  GenNonObjectVisitor<Const>::operator()(typename Const<MethodDecs>::type&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreached();
  }

  template <template <typename> class Const>
  void
  GenNonObjectVisitor<Const>::operator()(typename Const<MethodDec>::type&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreached();
  }

  template <template <typename> class Const>
  void
  GenNonObjectVisitor<Const>::operator()(typename Const<MethodCallExp>::type&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreached();
  }

  template <template <typename> class Const>
  void
  GenNonObjectVisitor<Const>::operator()(typename Const<ObjectExp>::type&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreached();
  }

} // namespace ast

#endif // !AST_NON_OBJECT_VISITOR_HXX
