/**
 ** \file ast/default-visitor.hh
 ** \brief Traverse an Abstract Syntax Tree (w/o objects), doing nothing.
 */

#ifndef AST_DEFAULT_VISITOR_HH
# define AST_DEFAULT_VISITOR_HH

# include <ast/visitor.hh>

namespace ast
{
  /** \brief Just visit the whole Ast tree (except object-related nodes).

      GenDefaultVisitor<CONSTNESS-SELECTOR> visits non-object-related
      node of the the whole Ast tree, but does nothing else.

      Beware, as there are no implementations visiting object-oriented
      constructs (classes, objects, methods), hence this class is
      abstract.

      ast::GenDefaultVisitor inherits virtually from ast::GenVisitor
      to allow diamond inheritance, e.g. so that a subclass of
      ast::GenDefaultVisitor can also inherit missing object-related
      implementations from another class (inheriting from
      ast::GenVisitor).

      \see ast::NonObjectVisitor for more information.  */
  template <template <typename> class Const>
  class GenDefaultVisitor : public virtual GenVisitor<Const>
  {
  public:
    /// Super class type.
    typedef GenVisitor<Const> super_type;

    // Import overloaded \c operator() methods.
    using super_type::operator();

    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a default visitor.
    GenDefaultVisitor();
    /// Destroy a default visitor.
    virtual ~GenDefaultVisitor();
    /** \} */

    /* We cannot simply use `using super_type::operator()' here,
       otherwise the linker would complain about missing symbols for
       these methods:

         GenVisitor<id_traits>::operator() (ast::MethodDec&)
         GenVisitor<id_traits>::operator() (ast::MethodCallExp&)

       This behavior seems to come from the mix between diamond
       inheritance and templates.  We redefine the following operator
       (delegating to GenVisitor's operator()) as a workaround.  */
    virtual void operator()(typename Const<Ast>::type& e);

    /** \name Visit Variable related nodes.
     ** \{ */
    virtual void operator()(typename Const<SimpleVar>::type& e) override;
    virtual void operator()(typename Const<FieldVar>::type& e) override;
    virtual void operator()(typename Const<SubscriptVar>::type& e) override;
    virtual void operator()(typename Const<CastVar>::type& e) override;
    /** \} */


    /** \name Visit Expression related nodes.
     ** \{ */
    virtual void operator()(typename Const<NilExp>::type& e) override;
    virtual void operator()(typename Const<IntExp>::type& e) override;
    virtual void operator()(typename Const<StringExp>::type& e) override;
    virtual void operator()(typename Const<CallExp>::type& e) override;
    virtual void operator()(typename Const<OpExp>::type& e) override;
    virtual void operator()(typename Const<RecordExp>::type& e) override;
    virtual void operator()(typename Const<SeqExp>::type& e) override;
    virtual void operator()(typename Const<AssignExp>::type& e) override;
    virtual void operator()(typename Const<IfExp>::type& e) override;
    virtual void operator()(typename Const<WhileExp>::type& e) override;
    virtual void operator()(typename Const<ForExp>::type& e) override;
    virtual void operator()(typename Const<BreakExp>::type&) override;
    virtual void operator()(typename Const<LetExp>::type& e) override;
    virtual void operator()(typename Const<ArrayExp>::type& e) override;
    virtual void operator()(typename Const<CastExp>::type& e) override;
    virtual void operator()(typename Const<FieldInit>::type& e) override;
    /** \} */


    /** \name Visit Declaration related nodes.
     **
     ** Visiting declarations is simple, but there are many clauses.
     ** This is because in Tiger, the declarations are processed by
     ** chunks (a chunk of Function declarations, then Var or Type,
     ** then ...).
     ** So we have to explain
     ** \li How to visit a list of chunks;
     ** \li how to visit chunks of function, var, or type declarations;
     ** \li how to visit a single function, var, or type declaration.
     ** \{ */

    /// Visit a list of function, type and/or variables declarations.
    virtual void operator()(typename Const<DecsList>::type& e) override;

    /// Visit a Decs chunks.
    virtual void operator()(typename Const<Decs>::type& e);

    template <typename DecsType>
    /** \brief Visit a chunk (i.e., a list of Function, Var, and Type decs).
     **
     ** It is exactly the same in the three cases, so the code is
     ** factored via a template method. */
    void decs_visit(typename Const<DecsType>::type& e);

    /// Visit Var declarations.
    virtual void operator()(typename Const<VarDecs>::type& e) override;
    virtual void operator()(typename Const<VarDec>::type& e) override;

    /// Visit Function declarations.
    virtual void operator()(typename Const<FunctionDecs>::type& e) override;
    virtual void operator()(typename Const<FunctionDec>::type& e) override;

    /// Visit Type declarations.
    virtual void operator()(typename Const<TypeDecs>::type& e) override;
    virtual void operator()(typename Const<TypeDec>::type& e) override;

    /** \} */


    /** \name Visit Type related nodes.
     ** \{ */
    virtual void operator()(typename Const<NameTy>::type& e) override;
    virtual void operator()(typename Const<RecordTy>::type& e) override;
    virtual void operator()(typename Const<ArrayTy>::type& e) override;
    /** \} */


    /** \name Visit Field related nodes. */
    virtual void operator()(typename Const<Field>::type& e) override;
  };

  /// Shorthand for a const visitor.
  typedef GenDefaultVisitor<misc::constify_traits> DefaultConstVisitor;
  /// Shorthand for a non const visitor.
#ifdef SWIG
  %template() GenVisitor<misc::id_traits>;
  %template() GenDefaultVisitor<misc::id_traits>;
#endif
  typedef GenDefaultVisitor<misc::id_traits> DefaultVisitor;

} // namespace ast

# include <ast/default-visitor.hxx>

#endif // !AST_DEFAULT_VISITOR_HH
