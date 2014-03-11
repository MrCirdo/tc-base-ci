/**
 ** \file type/array.cc
 ** \brief Implementation for type/array.hh.
 */

#include <ostream>

#include <type/array.hh>

namespace type
{

  std::ostream&
  Array::dump(std::ostream& ostr) const
  {
    return ostr << "array of " << type_get();
  }

} // namespace type
