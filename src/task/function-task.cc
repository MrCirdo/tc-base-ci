/**
 ** \file task/function-task.cc
 ** \brief Implementation of task::FunctionTask.
 **
 */

#include <task/function-task.hh>

namespace task
{

  FunctionTask::FunctionTask(void (*callback) (),
                             const char* module_name, const char* desc,
                             const char* name,
                             std::string deps)
    : Task(name, module_name, desc, 0, deps)
    , execute_(callback)
  {}

  bool
  FunctionTask::check() const
  {
    return true;
  }

  void
  FunctionTask::execute() const
  {
    execute_();
  }

} //namespace task
