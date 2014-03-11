/**
 ** \file overload/type-checker.hh
 ** \brief Checking/translating an OverTiger program in a Tiger program.
 */

#ifndef OVERLOAD_TYPE_CHECKER_HH
# define OVERLOAD_TYPE_CHECKER_HH

# include <type/types.hh>
# include <type/type-checker.hh>
# include <overload/binder.hh>

namespace overload
{

  /// Perform type checking, allowing function overload, and compute
  /// the bindings of the functions.
  class TypeChecker : public type::TypeChecker
  {
  public:
    /// Superclass.
    typedef type::TypeChecker super_type;
    using super_type::operator();

  public:
    TypeChecker(overfun_bindings_type* overfun_bindings);
    virtual ~TypeChecker();

  // FIXME: Some code was deleted here.
  private:
    overfun_bindings_type* overfun_bindings_;
  };

} // namespace type

#endif // !OVERLOAD_TYPE_CHECKER_HH
