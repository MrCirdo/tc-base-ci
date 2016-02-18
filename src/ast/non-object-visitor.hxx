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
  GenNonObjectVisitor<Const>::operator()(const_t<ClassTy>&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreachable();
  }

  template <template <typename> class Const>
  void
  GenNonObjectVisitor<Const>::operator()(const_t<MethodDecs>&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreachable();
  }

  template <template <typename> class Const>
  void
  GenNonObjectVisitor<Const>::operator()(const_t<MethodDec>&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreachable();
  }

  template <template <typename> class Const>
  void
  GenNonObjectVisitor<Const>::operator()(const_t<MethodCallExp>&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreachable();
  }

  template <template <typename> class Const>
  void
  GenNonObjectVisitor<Const>::operator()(const_t<ObjectExp>&)
  {
    // We must not be here (there should be no object feature in plain Tiger).
    unreachable();
  }

} // namespace ast

#endif // !AST_NON_OBJECT_VISITOR_HXX
