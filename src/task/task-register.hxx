/**
 ** \file task/task-register.hxx
 ** \brief Inline methods of task::TaskRegister.
 **
 */

#ifndef TASK_TASK_REGISTER_HXX
# define TASK_TASK_REGISTER_HXX

# include <task/task-register.hh>

namespace task
{
  inline
  const misc::timer&
  TaskRegister::timer_get() const
  {
    return timer_;
  }

} // namespace task.

#endif // !TASK_TASK_REGISTER_HXX

