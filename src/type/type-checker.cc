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
  {
  }

  const Type*
  TypeChecker::type(ast::Typable& e)
  {
    if (!e.type_get())
      e.accept(*this);
    return e.type_get();
  }

  const Record*
  TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
    for (ast::Field* f : e)
      if (res->field_type(f->name_get()))
        error(*f, "identifier multiply defined", f->name_get());
      else
        // Build the type of the record.
        res->field_add(f->name_get(), *type(f->type_name_get()));
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
    if (*type(e) != expected)
      {
        type_mismatch(e, s, *e.type_get(), "expected", expected);
        e.type_set(&expected);
      }
  }

  void
  TypeChecker::check_type(ast::Dec& e,
                          const std::string& s, const Type& expected)
  {
    if (*type(e) != expected)
      {
        type_mismatch(e, s, *e.type_get(), "expected", expected);
        e.type_set(&expected);
      }
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

    check_types(loc, exp1, *type1.type_get(), exp2, *type2.type_get());
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
    type_default(e, e.def_get()->type_get());
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
    type_default(e, &Int::instance());
  }

  void
  TypeChecker::operator()(ast::StringExp& e)
  {
    type_default(e, &String::instance());
  }


  // Complex values.

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
  // FIXME: Some code was deleted here.
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
    type_default(e, new Named(e.name_get()));
    created_type_default(e, e.type_get());
  }

  // Bind the type body to its name.
  template <>
  void
  TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
    // The type being defined.
    const auto& defined_type = dynamic_cast<const Named&>(*e.type_get());

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
    typedef ast::AnyDecs<D> decs_type;

  // FIXME: Some code was deleted here.
  }


  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  void
  TypeChecker::operator()(ast::NameTy& e)
  {
    const ast::TypeDec* def = e.def_get();
    if (def)
      {
        const Type* def_type = def->type_get();
        assertion(def_type);
        type_default(e, def_type);
      }
    else if (e.name_get() == "int")
      type_default(e, &Int::instance());
    else if (e.name_get() == "string")
      type_default(e, &String::instance());
    else
      // DEF is neither a user-defined type nor a primitive type.
      abort();
  }

  void
  TypeChecker::operator()(ast::RecordTy& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::ArrayTy& e)
  {
    // Creates a type.
    created_type_default(e, new Array(*type(e.base_type_get())));
    type_default(e, e.created_type_get());
  }

}
