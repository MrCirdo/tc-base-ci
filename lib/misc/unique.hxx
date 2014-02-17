/**
 ** \file misc/unique.hxx
 ** \brief Inline implementation of misc::unique.
 */

#ifndef MISC_UNIQUE_HXX
# define MISC_UNIQUE_HXX

# include <misc/unique.hh>
# include <misc/contract.hh>

namespace misc
{
  // FIXME: Some code was deleted here.

  template <typename  T, class C>
  inline typename unique<T, C>::value_type&
  unique<T, C>::operator=(const value_type& rhs)
  {
    if (this != &rhs)
      obj_ = rhs.obj_;
    return *this;
  }

  template <typename T, class C>
  inline bool
  unique<T, C>::operator==(const value_type& rhs) const
  {
    return obj_ == rhs.obj_;
  }

  template <typename T, class C>
  inline bool
  unique<T, C>::operator!=(const value_type& rhs) const
  {
    return !operator==(rhs);
  }

  template <typename T, class C>
  inline bool
  unique<T, C>::operator<(const value_type& rhs) const
  {
    C cmp;
    assertion(obj_);
    assertion(rhs.obj_);
    return cmp(*obj_, *rhs.obj_);
  }

  template <typename T, class C>
  inline std::ostream&
  operator<<(std::ostream& ostr, const unique<T, C>& the)
  {
    return ostr << the.object_get();
  }

}

#endif // !MISC_UNIQUE_HXX
