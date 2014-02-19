/**
 ** \file ast/visitor.hh
 ** \brief Definition of ast::Visitor.
 */

#ifndef AST_VISITOR_HH
# define AST_VISITOR_HH

# include <functional>
# include <ast/fwd.hh>
# include <misc/select-const.hh>

namespace ast
{

  /** \brief Root class of all Ast visitors.
   **
   ** GenVisitor<CONSTIFY> is the root class of all Ast visitors. */
  template <template <typename> class Const>
  class GenVisitor : public std::unary_function<Ast, void>
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Destroy a GenVisitor.
    virtual ~GenVisitor();
    /** \} */

    /// The entry point: visit \a e.
    virtual void operator()(typename Const<Ast>::type& e);
    virtual void operator()(typename Const<ArrayExp>::type&) = 0;
    virtual void operator()(typename Const<ArrayTy>::type&) = 0;
    virtual void operator()(typename Const<AssignExp>::type&) = 0;
    virtual void operator()(typename Const<BreakExp>::type&) = 0;
    virtual void operator()(typename Const<CallExp>::type&) = 0;
    virtual void operator()(typename Const<CastExp>::type&) = 0;
    virtual void operator()(typename Const<CastVar>::type&) = 0;
    virtual void operator()(typename Const<ClassTy>::type&) = 0;
    virtual void operator()(typename Const<DecsList>::type&) = 0;
    virtual void operator()(typename Const<Field>::type&) = 0;
    virtual void operator()(typename Const<FieldInit>::type&) = 0;
    virtual void operator()(typename Const<FieldVar>::type&) = 0;
    virtual void operator()(typename Const<ForExp>::type&) = 0;
    virtual void operator()(typename Const<FunctionDec>::type&) = 0;
    virtual void operator()(typename Const<IfExp>::type&) = 0;
    virtual void operator()(typename Const<IntExp>::type&) = 0;
    virtual void operator()(typename Const<LetExp>::type&) = 0;
    virtual void operator()(typename Const<MethodCallExp>::type&) = 0;
    virtual void operator()(typename Const<MethodDec>::type&) = 0;
    virtual void operator()(typename Const<NameTy>::type&) = 0;
    virtual void operator()(typename Const<NilExp>::type&) = 0;
    virtual void operator()(typename Const<ObjectExp>::type&) = 0;
    virtual void operator()(typename Const<OpExp>::type&) = 0;
    virtual void operator()(typename Const<RecordExp>::type&) = 0;
    virtual void operator()(typename Const<RecordTy>::type&) = 0;
    virtual void operator()(typename Const<SeqExp>::type&) = 0;
    virtual void operator()(typename Const<SimpleVar>::type&) = 0;
    virtual void operator()(typename Const<StringExp>::type&) = 0;
    virtual void operator()(typename Const<SubscriptVar>::type&) = 0;
    virtual void operator()(typename Const<TypeDec>::type&) = 0;
    virtual void operator()(typename Const<VarDec>::type&) = 0;
    virtual void operator()(typename Const<WhileExp>::type&) = 0;

    virtual void operator()(typename Const<FunctionDecs>::type&) = 0;
    virtual void operator()(typename Const<MethodDecs>::type&) = 0;
    virtual void operator()(typename Const<TypeDecs>::type&) = 0;
    virtual void operator()(typename Const<VarDecs>::type&) = 0;

    /// Helper to visit nodes manipulated via a pointer.
    template <class E> void operator()(E* e);

  protected:
    /** A convenient shortcut for recurring code like this:

        \code
        if (e)
          e->accept(*this);
        \endcode

        However, the drawback of this approach is that it doesn't take
        care of the constness, and any \a const violation will be
        reported \em within the body of this method, not at its
        corresponding call site.

        We cannot use the misc/select_const.hh approach here, since
        the compiler cannot resolve a function overloaded or
        specialized on an associated type of a template.  E.g., writing
        \a accept like this:

        \code
        template <typename E>
        void accept(typename Const<E>::type* e);
        \endcode

        won't work directly.  Of course, one can help the compiler,
        providing it with \a E

        \code
        accept<ast::NameTy>(e.result_get());
        \endcode

        but this is painful.  */
    template <typename E>
    void accept(E* e);
  };

# define VISITOR_VISIT_NODE_(Z, N, Array)                      \
    virtual void operator()(ast::BOOST_PP_ARRAY_ELEM(N, Array)& e);

# define VISITOR_VISIT_NODES(Nodes)                    \
  BOOST_PP_REPEAT(BOOST_PP_ARRAY_SIZE(Nodes),          \
                 VISITOR_VISIT_NODE_,                  \
                 Nodes)

  /// Shorthand for a const visitor.
  typedef GenVisitor<misc::constify_traits> ConstVisitor;
  /// Shorthand for a non const visitor.
  typedef GenVisitor<misc::id_traits> Visitor;

} // namespace ast

# include <ast/visitor.hxx>

#endif // !AST_VISITOR_HH
