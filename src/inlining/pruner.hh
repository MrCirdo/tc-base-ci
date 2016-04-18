/**
 ** \file inlining/pruner.hh
 ** \brief Declaration of inlining::Pruner.
 */

#pragma once

#include <map>
#include <astclone/cloner.hh>
#include <misc/set.hh>

namespace inlining
{

  /// Prune useless function declarations within an AST.
  class Pruner : public astclone::Cloner
  {
  public:
    using super_type = astclone::Cloner;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build an Pruner.
    Pruner();

    /// \name Visit methods.
    /// \{
  public:
  // FIXME: Some code was deleted here.
    /// \}

  // FIXME: Some code was deleted here.
  };

} // namespace inlining
