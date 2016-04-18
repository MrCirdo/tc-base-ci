/**
 ** \file astclone/libastclone.hh
 ** \brief Declare functions and variables exported by the Astclone module.
 */

#pragma once

#include <ast/fwd.hh>

/// Cloning an ast::Ast.
namespace astclone
{

  /** \brief Make a deep copy of an AST.
   ** \param tree abstract syntax tree's root.
   ** \return the cloned AST.  */
  template <typename T>
  T*
  clone(const T& tree);


  template <typename A>
  using applicable = auto(const A&) -> A*;

  /// Have the pure function \a f side effect on \a t.
  template <typename A>
  void
  apply(applicable<A> f, A*& t);

} // namespace astclone

#include <astclone/libastclone.hxx>
