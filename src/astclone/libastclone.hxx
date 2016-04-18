#pragma once

#include <ast/exp.hh>
#include <astclone/libastclone.hh>
#include <astclone/cloner.hh>

// Define exported clone functions.
namespace astclone
{

  template <typename T>
  T*
  clone(const T& tree)
  {
    Cloner clone;
    clone(tree);
    return dynamic_cast<T*>(clone.result_get());
  }

  template <typename A>
  void
  apply(applicable<A> f, A*& t)
  {
    A* t2 = f(*t);
    std::swap(t, t2);
    delete t2;
  }

} // namespace astclone
