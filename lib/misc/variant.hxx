/**
 ** \file misc/variant.hxx
 ** \brief Implementation of misc::variant.
 **/

#ifndef MISC_VARIANT_HXX
# define MISC_VARIANT_HXX

# include <boost/variant/get.hpp>
# include <misc/variant.hh>

namespace misc
{

  template <typename T0, typename T1>
  variant<T0, T1>::variant() : super_type()
  {
    // NOTE TO USER :
    // Compile error from here indicates that the first bound
    // type is not default-constructible, and so variant cannot
    // support its own default-construction.
  }

  template <typename T0, typename T1>
  template <typename U>
  variant<T0, T1>::variant(const U& rhs) : super_type(rhs)
  {
  }

  template <typename T0, typename T1>
  template <typename U>
  variant<T0, T1>&
  variant<T0, T1>::operator=(const U& rhs)
  {
    // Don't assign to oneself.
    if (static_cast<const void*>(&rhs) == static_cast<const void*>(this))
      return *this;
    super_type::operator=(rhs);
    return *this;
  }

  template <typename T0, typename T1>
  variant<T0, T1>::operator T0&()
  {
    return boost::get<T0>(*this);
  }

  // FIXME: Some code was deleted here.

  template <typename T0, typename T1>
  variant<T0, T1>::operator const T0&() const
  {
    return boost::get<T0>(*this);
  }

  // FIXME: Some code was deleted here.

} // namespace misc

#endif // !MISC_VARIANT_HXX
