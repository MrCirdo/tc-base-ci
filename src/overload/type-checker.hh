/**
 ** \file overload/type-checker.hh
 ** \brief Checking/translating an OverTiger program in a Tiger program.
 */

#pragma once

#include <type/types.hh>
#include <type/type-checker.hh>
#include <overload/binder.hh>

namespace overload
{

  /** \brief Perform type checking, allowing function overload, and compute
   ** the bindings of the functions.
   **
   ** Inheritence is declared virtual to enable diamond inheritance with
   ** the OverfunTypeChecker (src/object/overfun-type-checker.hh), inheriting
   ** from overload::TypeChecker and object::TypeChecker, both inheriting from
   ** type::TypeChecker.
   **/
  class TypeChecker : virtual public type::TypeChecker
  {
  public:
    /// Superclass.
    using super_type = type::TypeChecker;
    using super_type::operator();

  public:
    TypeChecker(overfun_bindings_type* overfun_bindings);
    virtual ~TypeChecker();

  // FIXME: Some code was deleted here.
  private:
    overfun_bindings_type* overfun_bindings_;
  };

} // namespace type
