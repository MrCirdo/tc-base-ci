/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <ast/all.hh>
#include <type/types.hh>
#include <type/type-checker.hh>


namespace type
{

  TypeChecker::TypeChecker()
    : super_type()
    , error_()
  {}

  const Type*
  TypeChecker::type(ast::Typable& e)
  {
  // FIXME: Some code was deleted here.
  }

  const Record*
  TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
  // FIXME: Some code was deleted here.
    return res;
  }

  const Record*
  TypeChecker::type(const ast::VarDecs& e)
  {
    auto res = new Record;
    for (const ast::VarDecs::Ds::value_type& i : e.decs_get())
      res->field_add(i->name_get(), *type(*i));

    return res;
  }

  const misc::error&
  TypeChecker::error_get() const
  {
    return error_;
  }


  /*-----------------.
  | Error handling.  |
  `-----------------*/

  void
  TypeChecker::error(const ast::Ast& loc, const std::string& msg)
  {
    error_ << misc::error::type
           << loc.location_get() << ": " << msg << std::endl;
  }

  void
  TypeChecker::type_mismatch(const ast::Ast& loc,
                             const std::string& exp1, const Type& type1,
                             const std::string& exp2, const Type& type2)
  {
    error_ << misc::error::type
           << loc.location_get() << ": type mismatch" << misc::incendl
           << exp1 << " type: " << type1 << misc::iendl
           << exp2 << " type: " << type2 << misc::decendl;
  }

  void
  TypeChecker::check_type(ast::Exp& e,
                          const std::string& s, const Type& expected)
  {
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::check_type(ast::Dec& e,
                          const std::string& s, const Type& expected)
  {
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::check_types(const ast::Ast& loc,
                           const std::string& exp1, const Type& type1,
                           const std::string& exp2, const Type& type2)
  {
  // FIXME: Some code was deleted here.
  }


  void
  TypeChecker::check_types(const ast::Ast& loc,
                           const std::string& exp1, ast::Typable& type1,
                           const std::string& exp2, ast::Typable& type2)
  {
    // Ensure evaluation order.
    type(type1);
    type(type2);
  // FIXME: Some code was deleted here (Check types).
  }


  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void
  TypeChecker::operator()(ast::SimpleVar& e)
  {
  // FIXME: Some code was deleted here.
  }

  // FIXME: Some code was deleted here.



  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // Literals.
  void
  TypeChecker::operator()(ast::NilExp& e)
  {
    type_default(e, &Nil::instance());
  }

  void
  TypeChecker::operator()(ast::IntExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::StringExp& e)
  {
  // FIXME: Some code was deleted here.
  }


  // Complex values.

  void
  TypeChecker::operator()(ast::RecordExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::OpExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  // FIXME: Some code was deleted here.


  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  void
  TypeChecker::operator()(ast::FunctionDecs& e)
  {
    decs_visit<ast::FunctionDec>(e);
  }


  void
  TypeChecker::operator()(ast::FunctionDec&)
  {
    // We must not be here.
    unreached();
  }


  // Store the type of this function.
  template <>
  void
  TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
  }


  // Type check this function's body.
  template <>
  void
  TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    visit_routine_body<type::Function>(e);
  }


  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void
  TypeChecker::operator()(ast::VarDec& e)
  {
  // FIXME: Some code was deleted here.
  }


  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

  void
  TypeChecker::operator()(ast::TypeDecs& e)
  {
    decs_visit<ast::TypeDec>(e);
  }


  void
  TypeChecker::operator()(ast::TypeDec&)
  {
    // We must not be here.
    unreached();
  }


  // Store this type.
  template <>
  void
  TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    // We only process the head of the type declaration, to set its
    // name in E.  A declaration has no type in itself; here we store
    // the type declared by E.
  // FIXME: Some code was deleted here.
  }

  // Bind the type body to its name.
  template <>
  void
  TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
  // FIXME: Some code was deleted here.
  }

  /*------------------.
  | Visiting /Decs/.  |
  `------------------*/

  template <class D>
  void
  TypeChecker::decs_visit(ast::AnyDecs<D>& e)
  {
    // Shorthand.
    using decs_type = ast::AnyDecs<D>;

  // FIXME: Some code was deleted here.
  }


  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  void
  TypeChecker::operator()(ast::NameTy& e)
  {
  // FIXME: Some code was deleted here (Recognize user defined types, and built-in types).
  }

  void
  TypeChecker::operator()(ast::RecordTy& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::ArrayTy& e)
  {
  // FIXME: Some code was deleted here.
  }

}
