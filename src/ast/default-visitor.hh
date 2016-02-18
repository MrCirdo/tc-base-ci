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
    using super_type = GenVisitor<Const>;

    // Import overloaded \c operator() methods.
    using super_type::operator();

    /// Convenient abbreviation.
    template <typename Type>
    using const_t = typename Const<Type>::type;

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
    virtual void operator()(const_t<Ast>& e) override;

    /** \name Visit Variable related nodes.
     ** \{ */
    virtual void operator()(const_t<SimpleVar>& e) override;
    virtual void operator()(const_t<FieldVar>& e) override;
    virtual void operator()(const_t<SubscriptVar>& e) override;
    virtual void operator()(const_t<CastVar>& e) override;
    /** \} */


    /** \name Visit Expression related nodes.
     ** \{ */
    virtual void operator()(const_t<NilExp>& e) override;
    virtual void operator()(const_t<IntExp>& e) override;
    virtual void operator()(const_t<StringExp>& e) override;
    virtual void operator()(const_t<CallExp>& e) override;
    virtual void operator()(const_t<OpExp>& e) override;
    virtual void operator()(const_t<RecordExp>& e) override;
    virtual void operator()(const_t<SeqExp>& e) override;
    virtual void operator()(const_t<AssignExp>& e) override;
    virtual void operator()(const_t<IfExp>& e) override;
    virtual void operator()(const_t<WhileExp>& e) override;
    virtual void operator()(const_t<ForExp>& e) override;
    virtual void operator()(const_t<BreakExp>&) override;
    virtual void operator()(const_t<LetExp>& e) override;
    virtual void operator()(const_t<ArrayExp>& e) override;
    virtual void operator()(const_t<CastExp>& e) override;
    virtual void operator()(const_t<FieldInit>& e) override;
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
    virtual void operator()(const_t<DecsList>& e) override;

    /// Visit a Decs chunks.
    virtual void operator()(const_t<Decs>& e);

    template <typename DecsType>
    /** \brief Visit a chunk (i.e., a list of Function, Var, and Type decs).
     **
     ** It is exactly the same in the three cases, so the code is
     ** factored via a template method. */
    void decs_visit(const_t<DecsType>& e);

    /// Visit Var declarations.
    virtual void operator()(const_t<VarDecs>& e) override;
    virtual void operator()(const_t<VarDec>& e) override;

    /// Visit Function declarations.
    virtual void operator()(const_t<FunctionDecs>& e) override;
    virtual void operator()(const_t<FunctionDec>& e) override;

    /// Visit Type declarations.
    virtual void operator()(const_t<TypeDecs>& e) override;
    virtual void operator()(const_t<TypeDec>& e) override;

    /** \} */


    /** \name Visit Type related nodes.
     ** \{ */
    virtual void operator()(const_t<NameTy>& e) override;
    virtual void operator()(const_t<RecordTy>& e) override;
    virtual void operator()(const_t<ArrayTy>& e) override;
    /** \} */


    /** \name Visit Field related nodes. */
    virtual void operator()(const_t<Field>& e) override;
  };

  /// Shorthand for a const visitor.
  using DefaultConstVisitor = GenDefaultVisitor<misc::constify_traits>;
  /// Shorthand for a non const visitor.
#ifdef SWIG
  %template() GenVisitor<misc::id_traits>;
  %template() GenDefaultVisitor<misc::id_traits>;
#endif
  using DefaultVisitor = GenDefaultVisitor<misc::id_traits>;

} // namespace ast

# include <ast/default-visitor.hxx>

#endif // !AST_DEFAULT_VISITOR_HH
