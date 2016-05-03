/**
 ** \file tree/const.hxx
 ** \brief Inline methods for tree/const.hh.
 **/

#pragma once

#include <tree/const.hh>

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
