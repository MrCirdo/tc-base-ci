/**
 ** \file object/renamer.cc
 ** \brief Implementation of object::Renamer.
 */

#include <object/renamer.hh>

namespace object
{
  using namespace ast;

  Renamer::Renamer()
    : super_type()
    , class_names_(new class_names_type)
    , within_class_ty_(false)
  {
    // Give a name to the built-in class Object.
    misc::put(*class_names_, &type::Class::object_instance(), "Object");
  }

  /*----------------------------.
  | Visiting definition sites.  |
  `----------------------------*/

  void
  Renamer::operator()(ast::VarDec& e)
  {
    if (within_class_ty_)
      // Don't rename class attributes.
      super_type::super_type::operator()(e);
    else
      // But still rename other variable declarations.
      super_type::operator()(e);
  }

  void
  Renamer::operator()(ast::MethodDecs& e)
  {
  // FIXME: Some code was deleted here (Just recurse on children nodes).
  }

  void
  Renamer::operator()(ast::MethodDec& e)
  {
    bool saved_within_class_ty = within_class_ty_;
    within_class_ty_ = false;
    /* We can't call bind::Binder::visit directly, because this method
       delegates the recursion task to DefaultVisitor, which doesn't
       have a proper operator() for MethodDec.  This visitor however
       knows how to handle a FunctionDec; therefore we upcast the
       MethodDec to a FunctionDec before visiting it.  */
    ast::FunctionDec& fundec = e;
    visit(fundec, &fundec);
    within_class_ty_= saved_within_class_ty;
  }

  // FIXME: Why operating on TypeDecs (with *s*) and not directly on
  // TypeDec (without s)?
  void
  Renamer::operator()(ast::TypeDecs& e)
  {
    // Rename.
  // FIXME: Some code was deleted here.

    // Collect the name of the classes.
  // FIXME: Some code was deleted here.
  }

  /*-----------------------.
  | Visiting usage sites.  |
  `-----------------------*/

  void
  Renamer::operator()(ast::MethodCallExp& e)
  {
    /* We can't rely on bind::Binder::visit, because this method
       delegates the recursion task to DefaultVisitor, which doesn't
       have a proper operator() for MethodCallExp.  Perfom the
       traversal by hand, as well as the renaming of the method
       name.  */
    misc::for_each(e.args_get(), *this);
    e.object_get().accept(*this);
    e.name_set(new_name(*e.def_get()));
  }

  /*--------------------------------------.
  | Visiting other object-related nodes.  |
  `--------------------------------------*/

  void
  Renamer::operator()(ast::ClassTy& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Renamer::operator()(ast::ObjectExp& e)
  {
    e.type_name_get().accept(*this);
  }

  /*------------------------------------------.
  | Visiting other non-object related nodes.  |
  `------------------------------------------*/

  // FIXME: Some code was deleted here.

  /*--------------.
  | Class names.  |
  `--------------*/

  class_names_type*
  Renamer::class_names_get() const
  {
    return class_names_;
  }

} // namespace object
