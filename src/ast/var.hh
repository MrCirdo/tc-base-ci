/**
 ** \file ast/var.hh
 ** \brief Declaration of ast::Var.
 */

#ifndef AST_VAR_HH
# define AST_VAR_HH

# include <ast/exp.hh>

namespace ast
{

  /// Var.
  class Var : public Exp
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Var node.
    Var(const Location& location);
    /// Destroy a Var node.
    virtual ~Var();
    /** \} */
  };

} // namespace ast

# include <ast/var.hxx>

#endif // !AST_VAR_HH
