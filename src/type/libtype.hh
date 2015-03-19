/**
 ** \file type/libtype.hh
 ** \brief Declare the function exported by type module.
 */

#ifndef TYPE_LIBTYPE_HH
# define TYPE_LIBTYPE_HH

# include <misc/error.hh>
# include <ast/fwd.hh>

/// Type-checking an ast::Ast.
namespace type
{

  /** \brief Check types in a (bound) AST.
   ** \param tree   abstract syntax tree's root.
   ** \return       synthesis of the errors possibly found. */
  misc::error types_check(::ast::Ast& tree);

} // namespace type

#endif // !TYPE_LIBTYPE_HH
