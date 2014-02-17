/**
 ** \file misc/generic-variant.hh
 ** \brief Interface of misc::generic_variant.
 **
 ** misc::generic_variant is a wrapper over boost::variant that adds
 ** conversion operators to the original Boost variant class.
 **
 ** \sa misc::variant
 **
 ** This class is not used in the Tiger Compiler.  It has been left
 ** here as an example of wrapper around a Boost class, showing
 ** interesting (but quite delicate) features such as the Boost
 ** Preprocessor Library (a set of macros for preprocessor
 ** metaprogramming).
 **
 ** misc::generic_variant is used just like boost::variant, and you
 ** won't be disturbed when using it.  Unfortunately, its
 ** implementation code is very difficult to read.  Hence, a simpler
 ** version of this class (where the number of underlying types in the
 ** variant is fixed) is provided, misc::variant.  This is the one
 ** actually used in the compiler.
 **/

#ifndef MISC_GENERIC_VARIANT_HH
# define MISC_GENERIC_VARIANT_HH

# include <boost/variant.hpp>
# include <boost/preprocessor/repetition/repeat_from_to.hpp>

/// \def Template parameter list for misc::variant declaration.
///
/// These macros have been adapted from boost/variant/variant_fwd.hpp.
/// \{
# define MISC_GENERIC_VARIANT_AUX_DECLARE_PARAMS_IMPL(z, N, T)               \
   typename BOOST_PP_CAT(T, N) = BOOST_PP_CAT(boost::detail::variant::void, N)

# define MISC_GENERIC_VARIANT_AUX_DECLARE_PARAMS        \
    BOOST_PP_ENUM(                                      \
          BOOST_VARIANT_LIMIT_TYPES                     \
        , MISC_GENERIC_VARIANT_AUX_DECLARE_PARAMS_IMPL  \
        , T                                             \
        )
/// \}

// Distinct void ``tags'' trick, copied from boost/variant/variant_fwd.hpp.
# define BOOST_VARIANT_DETAIL_DEFINE_VOID_N(z, N, _)    \
    struct BOOST_PP_CAT(void, N);                      \
                                                        \
    template<>                                          \
    struct convert_void< BOOST_PP_CAT(void, N) >        \
    {                                                   \
        typedef mpl::na type;                           \
    };

namespace boost
{
  namespace detail
  {
    namespace variant
    {
      BOOST_PP_REPEAT(
            BOOST_VARIANT_LIMIT_TYPES
          , BOOST_VARIANT_DETAIL_DEFINE_VOID_N
          , _
          )
    }
  }
}

# undef BOOST_VARIANT_DETAIL_DEFINE_VOID_N

namespace misc
{

  /// \brief Forward declaration of misc::variant.
  ///
  /// This declaration assigns default types to all parameters except
  /// the first one.
  ///
  /// \see boost/variant/variant_fwd.hpp.
  template < MISC_GENERIC_VARIANT_AUX_DECLARE_PARAMS >
  class generic_variant;

} // namespace misc

# undef MISC_GENERIC_VARIANT_AUX_DECLARE_PARAMS_IMPL
# undef MISC_GENERIC_VARIANT_AUX_DECLARE_PARAMS

/// Conversion operators generators (declarations).
/// \{
# define MISC_GENERIC_VARIANT_CONVERSION_OPERATOR_DECL(z, N, T) \
   operator BOOST_PP_CAT(T,N) & ();
# define MISC_GENERIC_VARIANT_CONST_CONVERSION_OPERATOR_DECL(z, N, T)   \
   operator const BOOST_PP_CAT(T,N) & () const;
/// \}


namespace misc
{
  /// A wrapper over boost::variant supporting conversion operators.
  ///
  /// Preconditions:
  /// - Each type must be unique.
  /// - No type may be const-qualified.
  ///
  /// Proper declaration form:
  ///   misc::generic_variant<types>    (where types is a type-sequence)
  /// or
  ///   misc::generic_variant<T0,T1,...,Tn>  (where T0 is NOT a type-sequence)
  template <typename T0_, BOOST_VARIANT_ENUM_SHIFTED_PARAMS(typename T)>
  class generic_variant :
    public boost::variant<T0_, BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)>
  {
  public:
    /// The type of this variant.
    typedef generic_variant<T0_, BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)>
      self_type;
    /// Super type.
    typedef boost::variant<T0_, BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)>
      super_type;

    /// Constructors.
    /// \{
    generic_variant();
    template <typename U> generic_variant(const U& rhs);
    /// \}

    template <typename U> self_type& operator=(const U&);

    /// \brief Convert this variant to a value of type \a U.
    ///
    /// This conversion rely on boost::get.  In particular, if the
    /// conversion fails, a boost::bad_get exception is thrown.
    /// \{
    operator T0_& ();
    BOOST_PP_REPEAT_FROM_TO(
          1
        , BOOST_VARIANT_LIMIT_TYPES
        , MISC_GENERIC_VARIANT_CONVERSION_OPERATOR_DECL
        , T
        )
    /// \}

    /// Likewise, const version.
    /// \{
    operator const T0_& () const;
    BOOST_PP_REPEAT_FROM_TO(
          1
        , BOOST_VARIANT_LIMIT_TYPES
        , MISC_GENERIC_VARIANT_CONST_CONVERSION_OPERATOR_DECL
        , T
        )
    /// \}
  };

} // namespace misc

# undef MISC_GENERIC_VARIANT_CONST_CONVERSION_OPERATOR_DECL
# undef MISC_GENERIC_VARIANT_CONVERSION_OPERATOR_DECL

# include <misc/generic-variant.hxx>

#endif // !MISC_GENERIC_VARIANT_HH
