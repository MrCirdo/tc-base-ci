/**
 ** \file escapes/tasks.hh
 ** \brief Escapes module related tasks.
 */

#ifndef ESCAPES_TASKS_HH
# define ESCAPES_TASKS_HH

# include <task/libtask.hh>

namespace escapes
{

  /// The Tasks of the escapes module.
  namespace tasks
  {

    TASK_GROUP("3. Escapes");

    /// Compute variables escaping.
    TASK_DECLARE("e|escapes-compute",
                 "compute the escaping variables "
                 "and the functions requiring a static link",
                 escapes_compute, "bound");

    /// Display escaped variables.
    TASK_DECLARE("E|escapes-display",
                 "enable escape display in the AST",
                 escapes_display, "parse");


  } // namespace tasks

} // namespace parse

#endif // !ESCAPES_TASKS_HH
