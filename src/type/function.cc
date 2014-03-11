/**
 ** \file type/function.cc
 ** \brief Implementation for type/function.hh.
 */

#include <ostream>

#include <type/function.hh>

namespace type
{

  std::ostream&
  Function::dump(std::ostream& ostr) const
  {
    bool locally_hide_actual_types = true;
    return ostr << hide_actual_types.swap(locally_hide_actual_types)
                << *formals_ << " -> " << result_
                << hide_actual_types.swap(locally_hide_actual_types);
  }

  // FIXME: Some code was deleted here.

} // namespace type
