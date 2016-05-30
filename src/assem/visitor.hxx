/**
 ** \file assem/visitor.hxx
 ** \brief Visitors of Fragments of assembly.
 */

#pragma once

#include <misc/algorithm.hh>
#include <assem/visitor.hh>
#include <assem/fragment.hh>

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
  operator()(const_t<ProcFrag>&)
  {}

  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(const_t<DataFrag>&)
  {}

  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(const_t<Fragments>& frags)
  {
    misc::for_each(frags, *this);
  }

} // namespace assem
