/**
 ** \file ast/default-visitor.hxx
 ** \brief Implementation for ast/default-visitor.hh.
 */

#ifndef AST_DEFAULT_VISITOR_HXX
# define AST_DEFAULT_VISITOR_HXX

# include <misc/algorithm.hh>
# include <ast/all.hh>
# include <ast/default-visitor.hh>

namespace ast
{

  template <template <typename> class Const>
  GenDefaultVisitor<Const>::GenDefaultVisitor() :
    GenVisitor<Const>()
  {
  }

  template <template <typename> class Const>
  GenDefaultVisitor<Const>::~GenDefaultVisitor()
  {
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<Ast>::type& e)
  {
    super_type::operator()(e);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<SimpleVar>::type&)
  {
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<FieldVar>::type& e)
  {
    e.var_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<CastVar>::type& e)
  {
    e.var_get().accept(*this);
    e.ty_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<SubscriptVar>::type& e)
  {
    e.var_get().accept(*this);
    e.index_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<NilExp>::type&)
  {
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<IntExp>::type&)
  {
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<StringExp>::type&)
  {
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<CallExp>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<OpExp>::type& e)
  {
    e.left_get().accept(*this);
    e.right_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<RecordExp>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<SeqExp>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<AssignExp>::type& e)
  {
    e.var_get().accept(*this);
    e.exp_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<IfExp>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<WhileExp>::type& e)
  {
    e.test_get().accept(*this);
    e.body_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<ForExp>::type& e)
  {
    e.vardec_get().accept(*this);
    e.hi_get().accept(*this);
    e.body_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<BreakExp>::type&)
  {
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<LetExp>::type& e)
  {
    e.decs_get().accept(*this);
    e.body_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<ArrayExp>::type& e)
  {
    e.type_name_get().accept(*this);
    e.size_get().accept(*this);
    e.init_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<CastExp>::type& e)
  {
    e.exp_get().accept(*this);
    e.ty_get().accept(*this);
  }


  template < template<typename> class Const >
  void
  GenDefaultVisitor<Const>::operator()(typename Const<FieldInit>::type& e)
  {
    e.init_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<DecsList>::type& e)
  {
    misc::for_each(e.decs_get(), *this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<Decs>::type& e)
  {
    e.accept(*this);
  }

  template <template <typename> class Const>
  template <typename DecsType>
  inline void
  GenDefaultVisitor<Const>::decs_visit(typename Const<DecsType>::type& e)
  {
    // The compiler cannot know whether the entity `type' is a type
    // or some other kind.  We must help it by specifying `typename'.

    // The type of the argument of this function, with const preserved.
    typedef typename Const<DecsType>::type arg_type;
    // The type of the list contained by this argument, const preserved.
    // We need to use Const again, because getting a typedef from
    // a const class does not give a const typedef.
    typedef typename Const<typename arg_type::Ds>::type elt_type;
    // An iterator over this list, const_iterator if needed.
    typename misc::select_iterator<elt_type>::type i;
    for (i = e.decs_get().begin(); i != e.decs_get().end(); ++i)
      (*i)->accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<VarDecs>::type& e)
  {
    decs_visit<VarDecs>(e);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<VarDec>::type& e)
  {
    // `type_name' might be omitted.
    this->accept(e.type_name_get());
    // `init' can be null in case of formal parameter.
    this->accept(e.init_get());
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<FunctionDecs>::type& e)
  {
    decs_visit<FunctionDecs>(e);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<FunctionDec>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<TypeDecs>::type& e)
  {
    decs_visit<TypeDecs>(e);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<TypeDec>::type& e)
  {
    e.ty_get().accept(*this);
  }


  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<NameTy>::type&)
  {
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<RecordTy>::type& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<ArrayTy>::type& e)
  {
    e.base_type_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(typename Const<Field>::type& e)
  {
    e.type_name_get().accept(*this);
  }

} // namespace ast

#endif // !AST_DEFAULT_VISITOR_HXX
