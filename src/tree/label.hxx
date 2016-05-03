/**
 ** \file tree/label.hxx
 ** \brief Inline methods for tree/label.hh.
 **/

#pragma once

#include <tree/label.hh>

namespace tree
{

  inline
  Label::Label(const temp::Label& label)
    : Stm()
    , label_(label)
  {}

  inline temp::Label
  Label::label_get() const
  {
    return label_;
  }

}
