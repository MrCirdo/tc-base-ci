/**
 ** \file overload/binder.hh
 ** \brief Declaration of overload::Binder.
 **/

#pragma once

#include <map>
#include <list>
#include <bind/binder.hh>
#include <overload/over-table.hh>

namespace overload
{

  /// Type of the dictionary of potential function bindings.
  using overfun_bindings_type = std::map<ast::CallExp*,
                   std::list<ast::FunctionDec*>>;

  /** \brief Computing bindings with support for overloaded functions.
   **
   ** This visitor inherits from Binder, but redefines methods
   ** dealing with function declarations and uses, to allow
   ** overloading.
   **
   ** As overloading requires some knowledge of the type of the
   ** arguments of a function, no real function binding is done here.
   ** We store all potential function declarations (``homonyms'') for
   ** each function call, and we'll let the overload::TypeChecker
   ** decide later.
   **
   ** Inheritence is declared virtual to enable diamond inheritance with
   ** the OverfunBinder (src/object/overfun-binder.hh), inheriting from
   ** overload::Binder and object::Binder, both inheriting from bind::Binder.
   **/
  class Binder : virtual public bind::Binder
  {
  public:
    /// Super class type.
    using super_type = bind::Binder;
    /// Import all the overloaded operator() methods.
    using super_type::operator();

    /** \name Overriden scope manipulations.
     ** \{ */
  protected:
    void scope_begin() override;
    void scope_end() override;
    /** \} */


    /* The visiting methods. */
  public:
    /// Visit a function call.
    void operator()(ast::CallExp& e) override;

    /// Check a function declaration header.
    void visit_dec_header(ast::FunctionDec& e);
    /// Visit a chunk of function declarations.
    void operator()(ast::FunctionDecs& e) override;

  public:
    /// Return the function bindings.
    overfun_bindings_type* overfun_bindings_get();

  private:
    using overtable_type = OverTable<ast::FunctionDec>;
    /// The environment of (overloaded) functions.
    overtable_type overfuns_;
    /// The potential function bindings.
    overfun_bindings_type* overfun_bindings_ = new overfun_bindings_type();
  };

} // namespace overload
