/**
 ** \file ast/object-visitor.hh
 ** \brief Provide default visits for object-related nodes.
 */

#ifndef AST_OBJECT_VISITOR_HH
# define AST_OBJECT_VISITOR_HH

# include <ast/visitor.hh>

namespace ast
{
  /** GenObjectVisitor<CONSTNESS-SELECTOR> provides default visit
      methods for object-related nodes.  This class is meant to factor
      the code visiting object-related nodes.

      ast::GenObjectVisitor inherits virtually from ast::GenVisitor
      to allow diamond inheritance, notably for a ``compatibility''
      purpose with ast::GenDefaultVisitor.

      For instance, bind::Binder, a visitor that handles bindings for
      an AST without objects, inherits from ast::DefaultVisitor to
      factor default (``empty'') traversal implementations for
      non-object-related nodes, and from ast::ObjectVisitor for
      object-related nodes.

      \verbatim

                             /ast::Visitor/
                                   ^
                (virtual)          |          (virtual)
                    ,--------------+--------------.
                    |                             |
                    |                             |
          /ast::DefaultVisitor/         /ast::ObjectVisitor/
                    ^                             ^
                    |                             |
                    `--------------+--------------'
                                   |
                                   |
                              bind::Binder

      \endverbatim
  */
  template <template <typename> class Const>
  class GenObjectVisitor : virtual public GenVisitor<Const>
  {
  public:
    /// Super class type.
    typedef GenVisitor<Const> super_type;

    // Import overloaded virtual functions.
    using super_type::operator();

    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an object visitor.
    GenObjectVisitor();
    /// Destroy an object visitor.
    virtual ~GenObjectVisitor();
    /** \} */

    /// \name Object-related visits.
    /// \{
    virtual void operator()(typename Const<ClassTy>::type& e) override;

    virtual void operator()(typename Const<MethodDecs>::type& e) override;
    virtual void operator()(typename Const<MethodDec>::type& e) override;

    virtual void operator()(typename Const<MethodCallExp>::type& e) override;
    virtual void operator()(typename Const<ObjectExp>::type& e) override;
    /// \}
  };

  /// Shorthand for a const visitor.
  typedef GenObjectVisitor<misc::constify_traits> ObjectConstVisitor;
  /// Shorthand for a non const visitor.
#ifdef SWIG
  %template() GenVisitor<misc::id_traits>;
  %template() GenObjectVisitor<misc::id_traits>;
#endif
  typedef GenObjectVisitor<misc::id_traits> ObjectVisitor;

} // namespace ast

# include <ast/object-visitor.hxx>

#endif // !AST_OBJECT_VISITOR_HH
