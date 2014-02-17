/**
 ** \file task/string-task.cc
 ** \brief Implementation of task::StringTask.
 **
 */

#include <common.hh>
#include <iostream>
#include <task/string-task.hh>

namespace task
{

  StringTask::StringTask(std::string& var,
                         const char* module_name, const char* desc,
                         const char* name,
                         std::string deps)
    : Task(name, module_name, desc, 0, deps)
    , var_(var)
  {
    argname_set("STRING");
  }

  bool
  StringTask::check() const
  {
    if (!arg_get())
      {
        std::cerr << program_name
                  << ": missing argument" << std::endl;
        return false;
      }
    var_ = arg_get();
    return true;
  }

  void
  StringTask::execute() const
  {
    // Assignment done in check.
  }

} //namespace task
