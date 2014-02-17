/**
 ** \file task/int-task.cc
 ** \brief IntTask class implementation.
 **
 */

#include <cstdlib>
#include <iostream>

#include <common.hh>
#include <task/int-task.hh>

namespace task
{

  IntTask::IntTask(int& var, int min, int max,
                   const char* module_name, const char* desc,
                   const char* name,
                   std::string deps)
    : Task(name, module_name, desc, 0, deps)
    , var_(var)
    , min_(min)
    , max_(max)
  {
    argname_set("NUM");
  }

  bool
  IntTask::check() const
  {
    if (!arg_get())
      {
        std::cerr << program_name
                  << ": missing argument" << std::endl;
        return false;
      }
    char** end = nullptr;
    var_ = strtol(arg_get(), end, 10);
    if (end && *end && **end)
      {
        std::cerr << program_name
                  << ": expected an integer: " << arg_get() << std::endl;
        return false;
      }
    if (! (min_ <= var_ && var_ <= max_))
      {
        std::cerr << program_name
                  << ": invalid integer: " << var_ << std::endl;
        return false;
      }

    return true;
  }

  void
  IntTask::execute() const
  {
    // Assignment done in check.
  }

} //namespace task
