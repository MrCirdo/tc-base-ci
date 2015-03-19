/**
 ** \file type/field.cc
 ** \brief Implementation for type/field.hh.
 */

#include <ostream>

#include <type/field.hh>

namespace type
{

  Field::~Field()
  {}

  std::ostream&
  Field::dump(std::ostream& ostr) const
  {
    return ostr << name_get() << " : " << type_get();
  }

} // namespace type
