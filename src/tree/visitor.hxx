/**
 ** \file tree/visitor.hxx
 ** \brief Visitors of Fragments of intermediate representation.
 */

#ifndef TREE_VISITOR_HXX
# define TREE_VISITOR_HXX

# include <misc/algorithm.hh>
# include <tree/fragments.hh>
# include <tree/visitor.hh>

namespace tree
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
  {
  }

  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(typename Const<DataFrag>::type&)
  {
  }

  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(typename Const<Fragments>::type& frags)
  {
    misc::for_each(frags, *this);
  }

} // namespace tree

#endif // !TREE_VISITOR_HXX
