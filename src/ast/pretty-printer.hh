/**
 ** \file ast/pretty-printer.hh
 ** \brief Declaration of ast::PrettyPrinter.
 */

#ifndef AST_PRETTY_PRINTER_HH
# define AST_PRETTY_PRINTER_HH

# include <ast/default-visitor.hh>
# include <ast/object-visitor.hh>

namespace ast
{

  /// Visit an Ast and print the content of each node.
  class PrettyPrinter
    : virtual public DefaultConstVisitor
    , virtual public ObjectConstVisitor
  {
  public:
    typedef DefaultConstVisitor super_type;
    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build to print on \a ostr.
    PrettyPrinter(std::ostream& ostr);

    /// Visit methods.
    /// \{
    virtual void operator()(const SimpleVar& e);
    virtual void operator()(const FieldVar& e);
    virtual void operator()(const SubscriptVar& e);
    virtual void operator()(const CastVar& e);
  // FIXME: Some code was deleted here.
    virtual void operator()(const CastExp& e);
  // FIXME: Some code was deleted here.
    /// \}

  private:
    // Factor pretty-printing of RecordExp and RecordTy.
    template <typename RecordClass>
    void print_record(const RecordClass& e);

  protected:
    /// The stream to print on.
    std::ostream& ostr_;
  };


} // namespace ast

#endif // !AST_PRETTY_PRINTER_HH
