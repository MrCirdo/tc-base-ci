/**
 ** \file astclone/tasks.hh
 ** \brief Astclone module tasks.
 */

#ifndef ASTCLONE_TASKS_HH
# define ASTCLONE_TASKS_HH

# include <misc/fwd.hh>

# include <task/libtask.hh>

namespace astclone
{

  /// Tasks of the astclone module.
  namespace tasks
  {
    TASK_GROUP("2.5 Cloning");

    /// Clone ast::tasks::the_program, remove it, and replace it with
    /// its copy.
    TASK_DECLARE("clone", "clone the Ast", clone, "parse");

  } // namespace tasks

} // namespace astclone

#endif // !ASTCLONE_TASKS_HH
