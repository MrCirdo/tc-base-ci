/**
 ** \file object/renamer.hh
 ** \brief Implementation of object::Renamer.
 */

#ifndef OBJECT_RENAMER_HH
# define OBJECT_RENAMER_HH

# include <map>

# include <bind/renamer.hh>
# include <object/libobject.hh>

namespace object
{
  /// \brief Perform identifier renaming within an AST (in place),
  /// with support for objects.
  class Renamer : public bind::Renamer
  {
  public:
    typedef ::bind::Renamer super_type;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a Renamer.
    Renamer();

    // Visit methods.
  public:
    /// \name Visiting definition sites.
    /// \{
    /// This method is like bind::Binder's, but prevent the renaming
    /// of attributes.
    virtual void operator()(ast::VarDec& e) override;
    /// Rename methods.
    virtual void operator()(ast::MethodDecs& e) override;
    /// Rename a method.
    virtual void operator()(ast::MethodDec& e) override;
    /// In addition to performing the renaming, collect the name of
    /// the classes.
    virtual void operator()(ast::TypeDecs& e) override;
    /// \}

    /// \name Visiting usage sites.
    /// \{
    virtual void operator()(ast::MethodCallExp& e) override;
    /// \}

    /// \name Visiting other object-related nodes.
    ///
    /// These methods should be part of an ObjectDefaultVisitor, but
    /// our current design makes the implementation (and the use) of
    /// such a visitor difficult.
    /// \{
    virtual void operator()(ast::ClassTy& e) override;
    virtual void operator()(ast::ObjectExp& e) override;
    /// \}

    /// \name Visiting other non-object related nodes.
    ///
    /// These method are just wrappers around their homonyms from
    /// bind::Renamer, handling \a within_class_ty_.
    /// \{
    virtual void operator()(ast::ForExp& e) override;
    virtual void operator()(ast::FunctionDec& e) override;
    /// \}

    /// Class names.
    /// \{
  public:
    /// Get the class names.
    class_names_type* class_names_get() const;

  private:
    /// Dictionnary mapping class types to their names.
    class_names_type* class_names_;
    /// Are we in a class definition?
    bool within_class_ty_;
    /// \}
  };

} // namespace object

#endif // !OBJECT_RENAMER_HH
