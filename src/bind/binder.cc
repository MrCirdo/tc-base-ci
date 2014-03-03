/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <misc/contract.hh>

#include <ast/all.hh>
#include <bind/binder.hh>

namespace bind
{

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error&
  Binder::error_get() const
  {
    return error_;
  }

  // FIXME: Some code was deleted here (Error reporting).

  /*----------------.
  | Symbol tables.  |
  `----------------*/

  // FIXME: Some code was deleted here.

  /*---------.
  | Visits.  |
  `---------*/

  // FIXME: Some code was deleted here.


  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  // VarDecs usually contains a single element. But in the case of
  // formal parameters, the formal list is set in a VarDecs.
  // Then the usual decs_visit applies: 2 formal parameters with the
  // same name is an error.
  void
  Binder::operator()(ast::VarDecs& e)
  {
    decs_visit<ast::VarDec>(e);
  }

  template<>
  void
  Binder::visit_dec_header<ast::VarDec>(ast::VarDec&)
  {
  }

  template<>
  void
  Binder::visit_dec_body<ast::VarDec>(ast::VarDec& e)
  {
    operator()(e);
  }


  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  // FIXME: Some code was deleted here.


  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/
  // FIXME: Some code was deleted here.

} // namespace bind
