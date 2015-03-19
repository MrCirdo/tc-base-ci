/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <ostream>

#include <type/named.hh>

namespace type
{

  namespace
  {
    /// How many times did we go through Named::print?
    inline long int& indent(std::ostream& o)
    {
      // The slot to store the current indentation level.
      static const long int indent_index = std::ios::xalloc();
      return o.iword(indent_index);
    }
  }

  // FIXME: Some code was deleted here.

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Named).

} // namespace type
