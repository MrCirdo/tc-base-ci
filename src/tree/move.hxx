/**
 ** \file tree/move.hxx
 ** \brief Inline methods for tree/move.hh.
 **/

#pragma once

#include <tree/move.hh>

namespace tree
{

  inline
  Move::Move(const rExp& dst, const rExp& src)
    : Stm()
  {
    child_push_back(dst);
    child_push_back(src);
  }

  inline rExp
  Move::dst_get() const
  {
    return child_get(0).cast<Exp>();
  }

  inline rExp
  Move::src_get() const
  {
    return child_get(1).cast<Exp>();
  }

}
