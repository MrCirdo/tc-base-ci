/**
 ** \file task/multiple-string-task.cc
 ** \brief Implementation of task::MultipleStringTask.
 */

#include <common.hh>
#include <iostream>
#include <task/multiple-string-task.hh>

namespace task
{

  MultipleStringTask::MultipleStringTask(callback_type& cb,
                                         const char* module_name,
                                         const char* desc,
                                         const char* name,
                                         std::string deps)
    : Task(name, module_name, desc, 0, deps)
    , execute_(cb)
  {
    argname_set("DIR");
  }

  bool
  MultipleStringTask::check() const
  {
    if (!arg_get())
      {
        std::cerr << program_name
                  << ": missing argument" << std::endl;
        return false;
      }
    execute_(arg_get());
    return true;
  }

  void
  MultipleStringTask::execute() const
  {
  }
} //namespace task
