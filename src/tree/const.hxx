/**
 ** \file tree/const.hxx
 ** \brief Inline methods for tree/const.hh.
 **/

#ifndef TREE_CONST_HXX
# define TREE_CONST_HXX

# include <tree/const.hh>

namespace tree
{

  inline
  Const::Const(int value)
    : value_(value)
  {}

  inline const int&
  Const::value_get() const
  {
    return value_;
  }

}

#endif // !TREE_CONST_HXX
