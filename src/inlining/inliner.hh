/**
 ** \file inlining/inliner.hh
 ** \brief Declaration of inlining::Inliner.
 */

#ifndef INLINING_INLINER_HH
# define INLINING_INLINER_HH

# include <map>

# include <misc/set.hh>
# include <astclone/cloner.hh>
# include <misc/scoped-map.hh>

namespace inlining
{

  /// Perform inline expansion of functions.
  class Inliner : public astclone::Cloner
  {
  public:
    using super_type = astclone::Cloner;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build an Inliner.
    Inliner(const ast::Ast& tree);

    /// Destroy an Inliner.
    virtual ~Inliner();

    /// \name Visit methods.
    /// \{
  public:
  // FIXME: Some code was deleted here.
    /// \}

  private:
    /// Recursive functions of the program.
    misc::set<const ast::FunctionDec*> rec_funs_;

  // FIXME: Some code was deleted here.
  };

} // namespace inlining

#endif // !INLINING_INLINER_HH
