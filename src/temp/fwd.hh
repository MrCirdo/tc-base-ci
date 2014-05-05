/**
 ** \file temp/fwd.hh
 ** \brief Forward declarations of temp classes
 */

#ifndef TEMP_FWD_HH
# define TEMP_FWD_HH

# include <misc/list.hh>
# include <misc/symbol.hh>
# include <misc/set.hh>
# include <misc/endomap.hh>
# include <misc/fwd.hh>

namespace temp
{

  // From identifier.hh.
  template <template <typename Tag_> class Traits_>
  class Identifier;

  // From temp.hh.
  template <typename Tag_>
  struct temp_traits;
  typedef Identifier<temp_traits> Temp;
  typedef misc::endo_map<Temp> TempMap;
  typedef misc::list<Temp> temp_list_type;

  // From temp-set.hh.
  typedef misc::set<Temp> temp_set_type;

  // From label.hh.
  template <typename Tag_>
  struct label_traits;
  typedef Identifier<label_traits> Label;

  // From label-list.hh.
  typedef misc::list<Label> label_list_type;

}

#endif // !TEMP_FWD_HH
