/**
 ** \file misc/scoped-map.hh
 ** \brief Declaration of misc::scoped_map.
 **
 ** This implements a stack of dictionnaries.  Each time a scope is
 ** opened, a new dictionnary is added on the top of the stack; the
 ** dictionary is removed when the scope is closed.  Lookup of keys
 ** is done in the last added dictionnary first (LIFO).
 **
 ** In particular this class is used to implement symbol tables.
 **/

#ifndef MISC_SCOPED_MAP_HH
# define MISC_SCOPED_MAP_HH

#include <list>
#include <map>

namespace misc
{
  template <typename Key, typename Data>
  class scoped_map
  {
  // FIXME: Some code was deleted here (This needs to be done at TC-3).
  };

  template <typename Key, typename Data>
  std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl);

} // namespace misc

# include <misc/scoped-map.hxx>

#endif // !MISC_SCOPED_MAP_HH
