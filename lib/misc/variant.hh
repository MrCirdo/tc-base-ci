/**
 ** \file misc/variant.hh
 ** \brief Interface of misc::variant.
 **
 ** misc::variant is a wrapper over boost::variant adding conversion
 ** operators to the original Boost variant class.  This variant
 ** expects two parameters, whereas boost::variant can virtually work
 ** with an arbitrary number of parameters.
 **
 ** If you are curious and want to see a more complete wrapper of
 ** boost::variant, have a look at misc::generic_variant (this is
 ** not required to complete the project).
 **/

#ifndef MISC_VARIANT_HH
# define MISC_VARIANT_HH

# include <boost/variant.hpp>

namespace misc
{
  /// A wrapper over boost::variant (with two types) supporting
  /// conversion operators.
  ///
  /// Preconditions:
  /// - Each type must be unique.
  /// - No type may be const-qualified.
  ///
  /// Proper declaration form:
  ///   misc::variant<T0, T1>
  template <typename T0, typename T1>
  class variant : public boost::variant<T0, T1>
  {
  public:
    /// The type of this variant.
    typedef variant<T0, T1> self_type;
    /// Super type.
    typedef boost::variant<T0, T1> super_type;

    /// Constructors.
    /// \{
    variant();
    template <typename U> variant(const U& rhs);
    /// \}

    template <typename U> self_type& operator=(const U&);

    /// \brief Convert this variant to a value of type \a U.
    ///
    /// This conversion rely on boost::get.  In particular, if the
    /// conversion fails, a boost::bad_get exception is thrown.
    /// \{
    operator T0&();
    operator T1&();
    /// \}

    /// Likewise, const version.
    /// \{
    operator const T0&() const;
    operator const T1&() const;
    /// \}
  };

} // namespace misc

# include <misc/variant.hxx>

#endif // !MISC_VARIANT_HH
