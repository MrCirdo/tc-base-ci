/**
 ** \file type/attribute.cc
 ** \brief Implementation for type/attribute.hh.
 */

#include <ostream>

#include <type/attribute.hh>

namespace type
{

  Attribute::~Attribute()
  {}

  std::ostream&
  Attribute::dump(std::ostream& ostr) const
  {
    return ostr << name_get() << " : " << type_get();
  }

} // namespace type
