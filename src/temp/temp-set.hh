/**
 ** \file temp/temp-set.hh
 ** \brief Sets of temporaries.
 */

#ifndef TEMP_TEMP_SET_HH
# define TEMP_TEMP_SET_HH

# include <temp/temp.hh>
# include <misc/set.hh>

namespace temp
{

  /// A sorted set of Temp's.
  typedef misc::set<Temp> temp_set_type;

  /// Output a temp_set_type, sorted.
  std::ostream&
  operator<<(std::ostream& ostr, const temp_set_type& temps);

} // namespace temp

#endif // !TEMP_TEMP_SET_HH
