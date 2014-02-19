/**
 ** \file ast/ast.hh
 ** \brief Declaration of ast::Ast.
 */

#ifndef AST_AST_HH
# define AST_AST_HH

# include <ast/location.hh>
# include <ast/fwd.hh>

namespace ast
{

  /// Ast.
  class Ast
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct an Ast node.
    Ast(const Location& location);
    /// Destroy an Ast node.
    virtual ~Ast();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
  public:
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const = 0;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) = 0;
    /// \}

    /** \name Accessors.
     ** \{ */
  public:
    /// Return scanner position information.
    const Location& location_get() const;
    /// Set scanner position information.
    void location_set(const Location&);
    /** \} */

  protected:
    /// Scanner position information.
    Location location_;
  };

} // namespace ast

# include <ast/ast.hxx>

#endif // !AST_AST_HH
