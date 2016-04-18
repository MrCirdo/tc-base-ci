/**
 ** \file type/pretty-printer.hh
 ** \brief Print the type hierarchy.
 */

#pragma once

#include <type/default-visitor.hh>
#include <type/fwd.hh>

#include <ostream>

namespace type
{

  class PrettyPrinter : public DefaultConstVisitor
  {
  public:
    /// Super class type.
    using super_type = DefaultConstVisitor;

    // Import overloaded \c operator() methods.
    using super_type::operator();

    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a pretty printer.
    PrettyPrinter(std::ostream& ostr);
    /** \} */

    /** \name Visit basic types.
     ** \{ */
    virtual void operator()(const Nil& e) override;
    virtual void operator()(const Void& e) override;
    virtual void operator()(const Int& e) override;
    virtual void operator()(const String& e) override;
    /** \} */


    /** \name Visit composed types.
     ** \{ */
    virtual void operator()(const Named& e) override;
    virtual void operator()(const Array& e) override;
    virtual void operator()(const Record& e) override;
    virtual void operator()(const Class& e) override;
    virtual void operator()(const Function& e) override;
    /** \} */

    /** \name Visit Non type types.
     ** \{ */
    void operator()(const Attribute& e);
    void operator()(const Field& e);
    /** \} */

  private:
    /// The stream to print on.
    std::ostream& ostr_;
  };

  /// Overload redirection operator for Type.
  std::ostream& operator<<(std::ostream& ostr, const Type& t);

  /// Overload redirection operator for Attribute.
  std::ostream& operator<<(std::ostream& ostr, const Attribute& obj);

  /// Overload redirection operator for Field.
  std::ostream& operator<<(std::ostream& ostr, const Field& obj);

} // namespace type
