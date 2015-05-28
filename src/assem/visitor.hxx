/**
 ** \file assem/visitor.hxx
 ** \brief Visitors of Fragments of assembly.
 */

#ifndef ASSEM_VISITOR_HXX
# define ASSEM_VISITOR_HXX

# include <misc/algorithm.hh>
# include <assem/visitor.hh>
# include <assem/fragment.hh>

namespace assem
{

  template <template <typename> class Const>
  GenVisitor<Const>::~GenVisitor()
  {}


  template <template <typename> class Const>
  template <class E>
  void
  GenVisitor<Const>::operator()(E* e)
  {
    e->accept(*this);
  }


  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(typename Const<ProcFrag>::type&)
  {}

  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(typename Const<DataFrag>::type&)
  {}

  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(typename Const<Fragments>::type& frags)
  {
    misc::for_each(frags, *this);
  }

} // namespace assem

#endif // !ASSEM_VISITOR_HXX
