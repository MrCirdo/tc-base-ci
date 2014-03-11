/**
 ** \file desugar/bound-checking-visitor.hh
 ** \brief Declaration of desugar::BoundCheckingVisitor.
 */

#ifndef DESUGAR_BOUND_CHECKING_VISITOR_HH
# define DESUGAR_BOUND_CHECKING_VISITOR_HH

# include <map>
# include <parse/tweast.hh>
# include <astclone/cloner.hh>

namespace desugar
{

  /// \brief Add dynamic array bound checks while duplicating an AST.
  class BoundCheckingVisitor : public astclone::Cloner
  {
  public:
    /// Parent type.
    typedef astclone::Cloner super_type;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a BoundCheckingVisitor.
    BoundCheckingVisitor();

    /// Destroy a BoundCheckingVisitor.
    virtual ~BoundCheckingVisitor();


    /// \name Visit methods.
    /// \{
  public:
  // FIXME: Some code was deleted here.
    /// \}

  private:
    /// The bounds checking runtime.
    ///
    /// Additional definitions to insert in the prelude.
    static const std::string prelude;

    // Symbols would be nicer, but maps of symbols are
    // inconvenient since there is no default ctor.
    typedef std::map<const type::Array*, std::string> boxes_type;
    /// Map from an array type to the corresponding `box' type name.
    boxes_type boxes_;
  };

} // namespace desugar

#endif // !DESUGAR_BOUND_CHECKING_VISITOR_HH
