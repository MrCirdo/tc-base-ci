/**
 ** \file frame/access.hxx
 ** \brief Inline methods for frame/access.hh.
 */

#pragma once

#include <frame/access.hh>

namespace frame
{

  inline
  temp::Temp
  In_Register::temp_get() const
  {
    return temp_;
  }

  inline
  int
  In_Frame::offset_get() const
  {
    return offset_;
  }

}
