/**
 ** \file type/function.hxx
 ** \brief Inline methods for type::Function.
 */
#pragma once

#include <type/function.hh>
#include <misc/contract.hh>

namespace type
{
  inline
  Function::Function(const Record* formals, const Type& result)
    : result_(result)
  {
    precondition(formals);

    formals_ = formals;
  }

  inline
  Function::~Function()
  {
    delete formals_;
  }

  inline
  const Record&
  Function::formals_get() const
  {
    return *formals_;
  }

  inline
  const Type&
  Function::result_get() const
  {
    return result_;
  }

} // namespace type
