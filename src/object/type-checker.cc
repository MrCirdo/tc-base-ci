/**
 ** \file object/type-checker.cc
 ** \brief Implementation for object/type-checker.hh.
 */

#include <iostream>
#include <sstream>

#include <ast/all.hh>
#include <object/type-checker.hh>
#include <type/types.hh>

namespace object
{

  TypeChecker::TypeChecker()
    : super_type()
    , current_(nullptr)
    , within_methoddec_body_p_(false)
  {
    // Reset the subclasses of Object.  This is required if several
    // trees are processed during the compilation.
    type::Class::object_instance().subclasses_clear();

    // `self' variables are the only valid variables having a null
    // declaration site.  Use this property to tag them as read-only.
  // FIXME: Some code was deleted here.
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
    if (e.def_get())
      type_default(e, e.def_get()->type_get());
    else if (e.name_get() == "self" && current_)
      type_default(e, current_);
    else
      // We must not be here.
      unreached();
  }

  void
  TypeChecker::operator()(ast::FieldVar& e)
  {
    const type::Type* def_type = type(e.var_get());
    auto class_type = dynamic_cast <const type::Class*>(&def_type->actual());

    if (class_type)
      {
        const type::Type* field_type = class_type->attr_type(e.name_get());

        if (!field_type)
          return error_and_recover(e, "unknown attribute", e.name_get());

        type_default(e, field_type);
      }
    else
      super_type::operator()(e);
  }


  /*----------------.
  | Visiting /Ty/.  |
  `----------------*/

  // Handle the case of `Object'.
  void
  TypeChecker::operator()(ast::NameTy& e)
  {
    const ast::TypeDec* def = e.def_get();
    if (!def && e.name_get() == "Object")
      {
        type_default(e, &type::Class::object_instance());
        return;
      }
    else
      super_type::operator()(e);
  }


  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // FIXME: Some code was deleted here.


  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

  void
  TypeChecker::operator()(ast::TypeDecs& e)
  {
    // Visit the header and the body of the typedecs, as in
    // type::TypeChecker.
    super_type::operator()(e);

    // However, class members are not considered part of the body of
    // their class here; they are processed separately to allow valid
    // uses of the class from its members.
    for (ast::TypeDec* typedec : e.decs_get())
      {
        ast::Ty& ty = typedec->ty_get();
        auto classty = dynamic_cast<ast::ClassTy*>(&ty);
        if (classty)
          visit_dec_members(*classty);
      }
  }


  /*----------------------.
  | Visiting MethodDecs.  |
  `----------------------*/

  void
  TypeChecker::operator()(ast::MethodDecs& e)
  {
    // Two passes: once on headers, then on bodies.
    for (ast::MethodDec* m : e.decs_get())
      visit_dec_header(*m);
    for (ast::MethodDec* m : e.decs_get())
      visit_dec_body(*m);
  }

  // Store the type of this method.
  void
  TypeChecker::visit_dec_header(ast::MethodDec& e)
  {
    assertion(current_);

  // FIXME: Some code was deleted here.

    // Check for multiply definition in the current class.
    for (const type::Method* m : current_->meths_get())
      if (m->name_get() == e.name_get())
        return error(e, "method multiply defined", e.name_get());

    // Check for signature conformance w.r.t. super class, if applicable.
    const type::Method* super_meth_type = current_->meth_type(e.name_get());
    if (super_meth_type)
      check_types(e,
                  "local method `" + e.name_get().name_get() + "'",
                  *method_type,
                  "super method `" + e.name_get().name_get() + "'",
                  *super_meth_type);

    // Add the method to the current class's method list.
    current_->meth_add(method_type);
  }


  // Type check this method's body.
  void
  TypeChecker::visit_dec_body(ast::MethodDec& e)
  {
    precondition(!within_methoddec_body_p_);
    within_methoddec_body_p_ = true;
    visit_routine_body<type::Method>(e);
    within_methoddec_body_p_ = false;
  }



  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void
  TypeChecker::operator()(ast::VarDec& e)
  {
    super_type::operator()(e);
    /* If we are inside a class declaration, but not a within a
       method's body, then E is an attribute: record it into the
       CURRENT_ class.  */
    if (e.init_get() && current_ && !within_methoddec_body_p_)
      {
        assertion(e.init_get());

        if (current_->attr_type(e.name_get()))
          error(e, "attribute multiply defined", e.name_get());
        else
          current_->attr_add(&e);
      }
  }


  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  // Don't handle members, as visit_dec_members is in charge of this task.
  void
  TypeChecker::operator()(ast::ClassTy& e)
  {
    auto class_type = new type::Class();

    type_default(e, class_type);
    created_type_default(e, e.type_get());

  // FIXME: Some code was deleted here (Set the type of the super class).

    // Recursively update the list of subclasses of the super classes.
    for (const type::Class* c = class_type->super_get(); c;
         c = c->super_get())
      c->subclass_add(class_type);
  }

  // Handle the members of a class.
  void
  TypeChecker::visit_dec_members(ast::ClassTy& e)
  {
    const type::Type* type = e.type_get();
    assertion(type);
    auto class_type = dynamic_cast<const type::Class*>(type);
    assertion(class_type);

    type::Class* saved_class_type = current_;
    // Make the type writable, so that we can add references to the
    // types of the members.
    current_ = const_cast<type::Class*>(class_type);
    /* Even if it were the case, pretend we are not within a method,
       since we are inside a class definition, which ``overrides'' any
       (outer) enclosing method.  */
    bool saved_within_methoddec_body_p = within_methoddec_body_p_;
    within_methoddec_body_p_ = false;
    e.decs_get().accept(*this);
    // Set back the status we had before we visited the members.
    within_methoddec_body_p_ = saved_within_methoddec_body_p;
    current_ = saved_class_type;
  }

} // namespace object
