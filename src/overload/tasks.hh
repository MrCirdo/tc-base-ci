/**
 ** \file overload/tasks.hh
 ** \brief Overload module tasks.
 */

#ifndef OVERLOAD_TASKS_HH
# define OVERLOAD_TASKS_HH

# include <task/libtask.hh>
# include <overload/binder.hh>

namespace overload
{

  namespace tasks
  {

    extern overfun_bindings_type* the_overfun_bindings;

    TASK_GROUP("4.5 Type checking with overloading");

    /// Compute bindings, allowing function overloading.
    TASK_DECLARE("overfun-bindings-compute", "bind the identifiers, "
                 "allowing function overloading",
                 overfun_bindings_compute, "parse");

    /// Check for type violation, allowing function overloading.
    TASK_DECLARE("O|overfun-types-compute", "check for type violations, "
                 "allowing function overloading",
                 overfun_types_compute, "overfun-bindings-compute");

  } // namespace tasks

} // namespace overload

#endif // !OVERLOAD_TASKS_HH
