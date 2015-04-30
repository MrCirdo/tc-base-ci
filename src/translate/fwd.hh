/**
 ** \file translate/fwd.hh
 ** \brief Forward declarations for translate:: items.
 */

#ifndef TRANSLATE_FWD_HH
# define TRANSLATE_FWD_HH

# include <list>
# include <misc/fwd.hh>

namespace translate
{
  // From level.hh.
  class Level;

  // From access.hh.
  class Access;
  using access_list_type = std::list<const Access*>;

  // From exp.hh.
  class Exp;
  using rExp = misc::ref<Exp>;
}

#endif // !TRANSLATE_FWD_HH
