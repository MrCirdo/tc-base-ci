/**
 ** \file tree/binop.hxx
 ** \brief Inline methods for tree/binop.hh.
 **/

#pragma once

#include <tree/binop.hh>

namespace tree
{


  inline
  Binop::Binop(const Oper oper, const rExp& left, const rExp& right)
    : Exp()
    , oper_(oper)
  {
    child_push_back(left);
    child_push_back(right);
  }

  inline rExp
  Binop::left_get() const
  {
    return child_get(0).cast<Exp>();
  }

  inline rExp
  Binop::right_get() const
  {
    return child_get(1).cast<Exp>();
  }

  inline Binop::Oper
  Binop::oper_get() const
  {
    return oper_;
  }

}
