/**
 ** \file regalloc/tasks.hh
 ** \brief Declares the Regalloc tasks.
 */

#ifndef REGALLOC_TASKS_HH
# define REGALLOC_TASKS_HH

# include <task/libtask.hh>

namespace regalloc
{

  /// Tasks for register allocation..
  namespace tasks
  {
    TASK_GROUP("9. Register Allocation");

    /// Disable coalescing.
    BOOLEAN_TASK_DECLARE("asm-coalesce-disable", "disable coalescence",
                         asm_coalesce_disable_p, "");

    /// Enable register allocation trace.
    BOOLEAN_TASK_DECLARE("asm-trace", "trace register allocation",
                         asm_trace_p, "");

    TASK_DECLARE("s|asm-compute", "allocate the registers",
                 asm_compute, "inst-compute");

    TASK_DECLARE("S|asm-display", "display the final assembler",
                 asm_display, "asm-compute runtime-display inst-display");

  } // namespace tasks

} // namespace register

#endif // !REGALLOC_TASKS_HH
