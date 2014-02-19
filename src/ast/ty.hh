/**
 ** \file ast/ty.hh
 ** \brief Declaration of ast::Ty.
 */

#ifndef AST_TY_HH
# define AST_TY_HH

# include <ast/ast.hh>

namespace ast
{

  /// Ty.
  class Ty : public Ast
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Ty node.
    Ty(const Location& location);
    /// Destroy a Ty node.
    virtual ~Ty();
    /** \} */
  };

} // namespace ast

# include <ast/ty.hxx>

#endif // !AST_TY_HH
