/**
 ** \file object/type-checker.hh
 ** \brief Checking an ObjectTiger program in a Tiger program.
 */

#pragma once

#include <type/class.hh>
#include <type/types.hh>
#include <type/type-checker.hh>

namespace object
{

  /** \brief Perform type checking, allowing objects, and compute
   ** the bindings of the object's methods and fields.
   **
   ** Inheritence is declared virtual to enable diamond inheritance with
   ** the OverfunTypeChecker (src/object/overfun-type-checker.hh), inheriting
   ** from overload::TypeChecker and object::TypeChecker, both inheriting from
   ** type::TypeChecker.
   **/
  class TypeChecker : virtual public type::TypeChecker
  {
  public:
    /// Superclass.
    using super_type = type::TypeChecker;
    using super_type::operator();

  public:
    /// Construction.
    TypeChecker();

  protected:

    // ------------------------- //
    // The core of the visitor.  //
    // ------------------------- //

    // ---------------- //
    // Visiting /Var/.  //
    // ---------------- //

    virtual void operator()(ast::FieldVar& e);
    virtual void operator()(ast::SimpleVar& e);

    // --------------- //
    // Visiting /Ty/.  //
    // --------------- //

    virtual void operator()(ast::NameTy& e);

    // ---------------- //
    // Visiting /Exp/.  //
    // ---------------- //

    // Method exp.
    virtual void operator()(ast::IfExp& e);
    virtual void operator()(ast::ObjectExp& e);
    virtual void operator()(ast::MethodCallExp& e);


    // ---------------- //
    // Visiting /Dec/.  //
    // ---------------- //

    /** Visit a chunk of type declarations.

        This method is like type::TypeChecker's one, except that is
        processes class declarations in three steps, instead of two
        (visit the headers, then the bodies):

        <ol>
        <li>visit headers, as in type::TypeChecker;</li>
        <li>visit bodies, which ignore all members of the class;</li>
        <li>visit members, i.e., attributes and methods.</li>
        </ol>

        This way, a method of a class can use the type of this class
        (e.g., return \a self), as that type has been created in the
        second step, and the method is processed in the third.  */
    virtual void operator()(ast::TypeDecs& e);

    // Check a Method's declaration header.
    void visit_dec_header(ast::MethodDec& e);
    // Check a Method's declaration body.
    void visit_dec_body(ast::MethodDec& e);

    /// Visit a chunk of method declarations.
    virtual void operator()(ast::MethodDecs& e);

    /// Visit a single Variable Declaration.
    virtual void operator()(ast::VarDec& e);


    // --------------- //
    // Visiting /Ty/.  //
    // --------------- //

    // Visit a class definition \em without its members.
    virtual void operator()(ast::ClassTy& e);
    // Visit the members of a class.
    virtual void visit_dec_members(ast::ClassTy& e);


  private:
    /// Current visited class.
    type::Class* current_ = nullptr;
    /// Are we within an ast::MethodDec's body?
    bool within_methoddec_body_p_ = false;
  };

} // namespace type
