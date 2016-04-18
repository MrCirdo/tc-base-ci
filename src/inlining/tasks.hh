/**
 ** \file inlining/tasks.hh
 ** \brief Inlining module tasks.
 */

#pragma once

#include <config.h>
#include <misc/fwd.hh>
#include <task/libtask.hh>

namespace inlining
{

  /// Tasks of the inlining module.
  namespace tasks
  {
    TASK_GROUP("Inlining");


    /*-----------.
    | Inlining.  |
    `-----------*/

    /// Expand the body of functions at the call sites.
    TASK_DECLARE("inline", "inline functions", inline_expand,
                 "types-compute rename");



    /*-------------------.
    | Function pruning.  |
    `-------------------*/

    /// Prune unused function definitions from the AST.
    TASK_DECLARE("prune", "prune unused functions", prune, "types-compute");


  } // namespace tasks

} // namespace inlining
