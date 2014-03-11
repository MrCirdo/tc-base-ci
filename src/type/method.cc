/**
 ** \file type/method.cc
 ** \brief Implementation for type/method.hh.
 */

#include <iostream>
#include <type/method.hh>

namespace type
{

  Method::Method(const misc::symbol& name, const Class* owner,
                 const Record* formals, const Type& result,
                 ast::MethodDec* def)
    : Function(formals, result)
    , name_(name)
    , owner_(owner)
    , def_(def)
  {}

  Method::~Method()
  {}

  // FIXME: Some code was deleted here.

} // namespace type
