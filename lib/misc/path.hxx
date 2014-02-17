/**
 ** \file misc/path.hxx
 ** \brief Path: implements inline function of misc/path.hh
 */

#ifndef MISC_PATH_HXX
# define MISC_PATH_HXX

# include <misc/path.hh>

namespace misc
{
  inline std::ostream&
  operator<<(std::ostream& ostr, const path& p)
  {
    return p.dump(ostr);
  }

  inline bool
  path::absolute_get() const
  {
    return absolute_;
  }

  inline bool
  path::empty() const
  {
    return path_.empty();
  }
}

#endif // !MISC_PATH_HXX
