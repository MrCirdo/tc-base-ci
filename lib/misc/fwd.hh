/**
 ** \file misc/fwd.hh
 ** \brief Forward declarations for misc:: items.
 */

#ifndef MISC_FWD_HH
# define MISC_FWD_HH

namespace misc
{
  // From file-library.hh.
  class FileLibrary;

  // From list.hh.
  template <class T_> class list;

  // From map.hh.
  template <typename T, typename N> class Map;
  // From endomap.hh.
  template <typename T> class Endomap;

  // From ref.hh.
  template <typename T> class ref;

  // From select-const.hh.
  template <typename T> struct constify_traits;
  template <typename T> struct id_traits;

  // From symbol.hh.
  class symbol;

  // From xalloc.hh.
  template <class StoredType> class xalloc;

  // From timer.hh
  class Timer;
}

#endif // !MISC_FWD_HH
