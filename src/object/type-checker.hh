/**
 ** \file object/type-checker.hh
 ** \brief Checking an ObjectTiger program in a Tiger program.
 */

#ifndef OBJECT_TYPE_CHECKER_HH
# define OBJECT_TYPE_CHECKER_HH

# include <type/class.hh>
# include <type/types.hh>
# include <type/type-checker.hh>

namespace object
{

  /// Perform type checking, allowing objects, and compute
  /// the bindings of the object's methods and fields.
  class TypeChecker : public type::TypeChecker
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
    type::Class* current_;
    /// Are we within an ast::MethodDec's body?
    bool within_methoddec_body_p_;
  };

} // namespace type

#endif // !OBJECT_TYPE_CHECKER_HH
