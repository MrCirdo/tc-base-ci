/**
 ** \file misc/generic-variant.hxx
 ** \brief Implementation of misc::generic_variant.
 **/

#ifndef MISC_GENERIC_VARIANT_HXX
# define MISC_GENERIC_VARIANT_HXX

# include <boost/variant/get.hpp>
# include <boost/preprocessor/repetition/repeat_from_to.hpp>
# include <boost/preprocessor/punctuation/comma.hpp>
# include <misc/generic-variant.hh>

// Shortcuts.
// Save some bytes (this type and its parameters are so long to type!)
# define MISC_GENERIC_VARIANT_PARAMS                                          \
  typename T0_ BOOST_PP_COMMA() BOOST_VARIANT_ENUM_SHIFTED_PARAMS(typename T)
# define MISC_GENERIC_VARIANT_TYPE                                      \
    generic_variant<T0_ BOOST_PP_COMMA() BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)>

/// Conversion operators generators (definitions).
/// \{
# define MISC_GENERIC_VARIANT_CONVERSION_OPERATOR_DEF(z, N, T)  \
  template <MISC_GENERIC_VARIANT_PARAMS>                        \
  MISC_GENERIC_VARIANT_TYPE::operator BOOST_PP_CAT(T,N) & ()    \
  {                                                             \
    return boost::get<BOOST_PP_CAT(T,N)>(*this);               \
  }

# define MISC_GENERIC_VARIANT_CONST_CONVERSION_OPERATOR_DEF(z, N, T)     \
  template <MISC_GENERIC_VARIANT_PARAMS>                                 \
  MISC_GENERIC_VARIANT_TYPE::operator const BOOST_PP_CAT(T,N) & () const \
  {                                                                      \
    return boost::get<BOOST_PP_CAT(T,N)>(*this);                        \
  }
/// \}


namespace misc
{

  template <MISC_GENERIC_VARIANT_PARAMS>
  MISC_GENERIC_VARIANT_TYPE::generic_variant() : super_type()
  {
    // NOTE TO USER :
    // Compile error from here indicates that the first bound
    // type is not default-constructible, and so variant cannot
    // support its own default-construction.
  }

  template <MISC_GENERIC_VARIANT_PARAMS>
  template <typename U>
  MISC_GENERIC_VARIANT_TYPE::generic_variant(const U& rhs) : super_type(rhs)
  {
  }

  template <MISC_GENERIC_VARIANT_PARAMS>
  template <typename U>
  MISC_GENERIC_VARIANT_TYPE&
  MISC_GENERIC_VARIANT_TYPE::operator=(const U& rhs)
  {
    // Don't assign to oneself.
    if (static_cast<const void*>(&rhs) == static_cast<const void*>(this))
      return *this;
    super_type::operator=(rhs);
    return *this;
  }


  template <MISC_GENERIC_VARIANT_PARAMS>
  MISC_GENERIC_VARIANT_TYPE::operator T0_& ()
  {
    return boost::get<T0_>(*this);
  }

  BOOST_PP_REPEAT_FROM_TO(
        1
      , BOOST_VARIANT_LIMIT_TYPES
      , MISC_GENERIC_VARIANT_CONVERSION_OPERATOR_DEF
      , T
      )

  template <MISC_GENERIC_VARIANT_PARAMS>
  MISC_GENERIC_VARIANT_TYPE::operator const T0_& () const
  {
    return boost::get<T0_>(*this);
  }

  BOOST_PP_REPEAT_FROM_TO(
        1
      , BOOST_VARIANT_LIMIT_TYPES
      , MISC_GENERIC_VARIANT_CONST_CONVERSION_OPERATOR_DEF
      , T
      )

} // namespace misc

# undef MISC_GENERIC_VARIANT_CONVERSION_OPERATOR_DEF
# undef MISC_GENERIC_VARIANT_CONST_CONVERSION_OPERATOR_DEF
# undef MISC_GENERIC_VARIANT_TYPE
# undef MISC_GENERIC_VARIANT_PARAMS

#endif // !MISC_GENERIC_VARIANT_HXX
