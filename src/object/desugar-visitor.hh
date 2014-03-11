/**
 ** \file object/desugar-visitor.hh
 ** \brief Declaration of object::DesugarVisitor.
 */

#ifndef OBJECT_DESUGAR_VISITOR_HH
# define OBJECT_DESUGAR_VISITOR_HH

# include <astclone/cloner.hh>
# include <parse/tweast.hh>
# include <object/libobject.hh>

namespace object
{
  /// \brief Desugar some object structures while duplicating an Ast.
  class DesugarVisitor : public astclone::Cloner
  {
  public:
    /// Superclass.
    typedef astclone::Cloner super_type;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a DesugarVisitor.
    DesugarVisitor(const class_names_type& class_names);

    /// Destroy a DesugarVisitor.
    virtual ~DesugarVisitor();

  public:
    /// Special version of the visit of a DecsList allowing the
    /// transformation of an ast::Decs to either a single ast::Decs or
    /// to an ast::DecsList.
    virtual void operator()(const ast::DecsList& e) override;

    /// \name Desugar class declarations.
    /// \{

    /// Desugar class declarations.
    virtual void operator()(const ast::TypeDecs& e) override;
    /// Handle the builtin Object.
    virtual void operator()(const ast::FunctionDec& e) override;
    /// Desugar class names.
    virtual void operator()(const ast::NameTy& e) override;

    /// \}

    /// \name Desugar class instantiations and object usage.
    /// \{

    /// Desugar polymorphic initializations.
    virtual void operator()(const ast::VarDec& e) override;
    /// Desugar manifest objects.
    virtual void operator()(const ast::ObjectExp& e) override;
    /// Desugar polymorphic assignments.
    virtual void operator()(const ast::AssignExp& e) override;
    /// Add object casts around arguments when needed.
    virtual void operator()(const ast::CallExp& e) override;

    /// \}

    /// \name Desugar accesses to class members.
    /// \{

    /// Desugar accesses to attributes.
    virtual void operator()(const ast::FieldVar& e) override;
    /// Desugar calls to methods.
    virtual void operator()(const ast::MethodCallExp& e) override;

    /// \}

    /// \brief Desugar actuals arguments in routine calls.
    ///
    /// \param actuals      the actual arguments of the initial AST
    /// \param formals      the formal arguments of the routine
    /// \return             the desugared actual arguments
    virtual ast::exps_type* recurse_args(const ast::exps_type& actuals,
                                         const type::Record& formals);

    /// A list of classes (e.g., useful to represent a set of subclasses).
    typedef std::list<const type::Class*> classes_type;

  private:
    /// \name Code generation.
    /// \{

    /// \brief Return the name of a type.
    ///
    /// \param type         either a builtin type or a type::Named
    /// \result             the name of the type
    std::string type_symbol(const type::Type* type);

    /// Return the name of the upcast function between types \a from
    /// and \a to.
    std::string upcast_fun_name(const type::Class* from,
                                const type::Class* to);
    /// Return the name of the downcast function between types \a from
    /// and \a to.
    std::string downcast_fun_name(const type::Class* from,
                                  const type::Class* to);

    /// Return the name of the dispatch function for \a method,
    /// defined in class \a owner.
    std::string dispatch_fun_name(const type::Class* owner,
                                  const type::Method* method);

    /// Check if the type \a source_type of \a source_exp matches
    /// \a target_type, and generate a type conversion wrapper if
    /// needed.
    void adapt_type(ast::Exp*& source_exp, const type::Class* source_type,
                    const type::Class* target_type);

    /// The type of a list of initializations for the field of a variant.
    typedef misc::map<const type::Class*, std::string> field_inits_type;

    /// \brief Generate a variant expression.
    ///
    /// \param static_type  the type of the class whose variant is built
    /// \param exact_type   the exact type of the data stored in the variant
    /// \param inits        the initalization value of the variant (must be
    ///                     of type \a dynamic_type).
    /// \return             the generated variant expression
    ast::Exp* variant_exp(const type::Class* static_type,
                          const std::string& exact_type,
                          const field_inits_type& inits);

    /// Syntactic sugar for the previous routine.
    ast::Exp* variant_exp(const type::Class* static_type,
                          const type::Class* dynamic_type,
                          const field_inits_type& inits);

    /// \brief Generate code for a variant type on a TWEAST.
    ///
    /// Contrary to object::DesugarVisitor::variant_exp, we
    /// cannot directly generate an expression, since the client
    /// TWEAST won't accept an ast::Ty* as a metavariable.
    ///
    /// \param class_type   the type of the class whose variant is built
    /// \return             the TWEAST on which the code is generated
    parse::Tweast* variant_ty(const type::Class* class_type);

    /// \brief Generate a conversion routine.
    ///
    /// \param name         the type of the generated function
    /// \param source       the type of the converted value
    /// \param target       the target type of the conversion
    /// \param exact_type   the exact type of the returned variant
    /// \return             the TWEAST on which the code is generated
    parse::Tweast* cast_function(const std::string& name,
                                 const type::Class* source,
                                 const type::Class* target,
                                 const type::Class* exact_type);

    /// Syntactic sugar for object::DesugarVisitor::cast_function,
    /// used to generate an upcast function.
    parse::Tweast* upcast_function(const type::Class* source,
                                   const type::Class* target);

    /// Syntactic sugar for object::DesugarVisitor::cast_function,
    /// used to generate a downcast function.
    parse::Tweast* downcast_function(const type::Class* source,
                                     const type::Class* target);

    /// \brief Generate an expression looking like a switch
    /// expression, to dispatch a method call.
    ///
    /// \param class_type   the static type of the class owning the method
    /// \param method       the called method
    /// \return             the generated expression
    ast::Exp* dispatch_switch(const type::Class* class_type,
                              const type::Method* method);

    /// \brief Generate a (static) call to a desugared method.
    ///
    /// \note The dynamic dispatch must have been performed before
    /// using this generator.
    ///
    /// \param class_name   the class where the method resides
    /// \param method_name  the name of the method
    /// \param target       the name of the target (object)
    /// \param formals      the actual arguments (other than the target)
    /// \return             the TWEAST on which the code is generated
    parse::Tweast* method_call(const misc::symbol& class_name,
                               const misc::symbol& method_name,
                               const std::string& target,
                               const ast::VarDecs::Ds& formals);

    /// \}

  private:
    /// The names of the classes defined in the program.
    class_names_type class_names_;

    /// TWEAST of desugared types.
    parse::Tweast types_;
    /// TWEAST of class ids.
    parse::Tweast class_ids_;
  };

} // namespace object

#endif // !OBJECT_DESUGAR_VISITOR_HH
