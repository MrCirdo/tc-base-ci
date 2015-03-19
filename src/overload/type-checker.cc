/**
 ** \file overload/type-checker.cc
 ** \brief Implementation for overload/type-checker.hh.
 */

#include <sstream>

#include <misc/indent.hh>
#include <type/types.hh>
#include <overload/type-checker.hh>

namespace overload
{

  TypeChecker::TypeChecker(overfun_bindings_type* overfun_bindings)
    : overfun_bindings_(overfun_bindings)
  {}

  TypeChecker::~TypeChecker()
  {}

  // FIXME: Some code was deleted here.

} // namespace overload
