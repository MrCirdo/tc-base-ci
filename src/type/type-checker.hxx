/**
 ** \file type/type-checker.hxx
 ** \brief Inline methods of type::TypeChecker.
 */

#ifndef TYPE_TYPE_CHECKER_HXX
# define TYPE_TYPE_CHECKER_HXX

# include <ast/all.hh>
# include <type/types.hh>
# include <type/type-checker.hh>

namespace type
{

  /*----------------.
  | Setting types.  |
  `----------------*/

  // FIXME: Some code was deleted here.


  /*-----------------.
  | Error handling.  |
  `-----------------*/

  template <typename T>
  void
  TypeChecker::error(const ast::Ast& loc, const std::string& msg,
                     const T& exp)
  {
    error_ << misc::error::type
           << loc.location_get() << ": " << msg << ": " << exp << std::endl;
  }

  template <typename T, typename U>
  void
  TypeChecker::error_and_recover(T& loc, const std::string& msg, const U& exp)
  {
    error(loc, msg, exp);
    loc.type_set(&Int::instance());
  }


  template <typename Routine_Type, typename Routine_Node>
  void
  TypeChecker::visit_routine_body(Routine_Node& e)
  {
  // FIXME: Some code was deleted here.
  }
}

#endif // !TYPE_TYPE_CHECKER_HXX
