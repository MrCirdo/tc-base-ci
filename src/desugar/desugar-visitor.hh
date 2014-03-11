/**
 ** \file desugar/desugar-visitor.hh
 ** \brief Declaration of desugar::DesugarVisitor.
 */

#ifndef DESUGAR_DESUGAR_VISITOR_HH
# define DESUGAR_DESUGAR_VISITOR_HH

# include <map>
# include <astclone/cloner.hh>

namespace desugar
{

  /// \brief Desugar some syntactic structures while duplicating an Ast.
  class DesugarVisitor : public astclone::Cloner
  {
  public:
    /// Superclass.
    typedef astclone::Cloner super_type;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a DesugarVisitor.
    DesugarVisitor(bool desugar_for_p,
                   bool desugar_string_cmp_p);

    /// Destroy a DesugarVisitor.
    virtual ~DesugarVisitor();

    /// \name Visit methods.
    /// \{
  public:
    /// Desugar string comparisons.
    virtual void operator()(const ast::OpExp&) override;
    /// Desugar `for' loops as `while' loops.
    virtual void operator()(const ast::ForExp&) override;
    /// \}

  private:
    /// Desugar `for' loops?
    bool desugar_for_p_;
    /// Desugar string comparisons?
    bool desugar_string_cmp_p_;
  };

} // namespace desugar

#endif // !DESUGAR_DESUGAR_VISITOR_HH
