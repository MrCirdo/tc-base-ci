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
  typedef std::list<const Access*> access_list_type;

  // From exp.hh.
  class Exp;
  typedef misc::ref<Exp> rExp;
}

#endif // !TRANSLATE_FWD_HH
