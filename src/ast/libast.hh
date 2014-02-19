/**
 ** \file ast/libast.hh
 ** \brief Public ast interface declaration.
 */

#ifndef AST_LIBAST_HH
# define AST_LIBAST_HH

# include <iosfwd>
# include <ast/fwd.hh>

/// Ast management.
namespace ast
{

  extern const misc::xalloc<bool> escapes_display;

  /// Output \a a on \a ostr.
  std::ostream& operator<<(std::ostream& ostr, const Ast& tree);

} // namespace ast

#endif // !AST_LIBAST_HH
