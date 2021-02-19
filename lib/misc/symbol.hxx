/**
 ** \file misc/symbol.hxx
 ** \brief Inline implementation of misc::symbol.
 */

#pragma once

#include <iostream>
#include <misc/symbol.hh>

namespace misc
{
  inline symbol& symbol::operator=(const symbol& rhs)
  {
    unique::operator=(rhs);

    return *this;
  }

  inline bool symbol::operator==(const symbol& rhs) const
  {
    return unique::operator==(rhs);
  }

  inline bool symbol::operator!=(const symbol& rhs) const
  {
    return !operator==(rhs);
  }

  inline std::ostream& operator<<(std::ostream& ostr, const symbol& the)
  {
    std::cout << the.get();
  }

} // namespace misc
