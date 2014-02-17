/**
 ** \file task/task.cc
 ** \brief Implementation of task::Task.
 **
 */

#include <algorithm>
#include <iterator>
#include <iostream>

#include <common.hh>
#include <task/task.hh>
#include <task/task-register.hh>

namespace task
{

  Task::~Task()
  {}

  Task::Task(const char* name,
             const char* module_name, const char* desc,
             int key, const std::string& deps)
    : name_(normalize(name)), module_name_(module_name), desc_(desc)
    , argname_(nullptr), arg_(nullptr)
  {
    // Pseudo reference counter, for auto indexing.
    static int auto_key = -1;

    // Compute its dependencies.
    std::string::size_type start = 0;
    while (start < deps.size())
      {
        std::string::size_type end = deps.find(' ', start);
        if (end > deps.size())
          end = deps.size();
        dependencies_.push_back(normalize(deps.substr(start, end - start)));
        start = end + 1;
      }

    // See if it has a short option, such as "h|help".
    if (name_.size() >= 2 && name_[1] == '|')
      {
        if (key)
          task_error << misc::error::failure
                     << program_name
                     << ": Task::Task(" << name_
                     << "): both key and short option are provided"
                     << std::endl;
        key = name_[0];
        name_.erase(0, 2);
      }

    // Register this task.
    key_ = (key == 0) ? --auto_key : key;
    TaskRegister::instance().register_task(*this);
  }


  Task::deps_type
  Task::resolve_dependencies(tasks_list_type&) const
  {
    // By default, consider that all dependencies are required.
    return dependencies_;
  }


  /// Display dependencies of this task.
  void
  Task::print_dependencies() const
  {
    std::cout << "Dependencies for task " << name_ << ":" << std::endl;
    for (const std::string& s : dependencies_)
      std::cout << "\t" << s << std::endl;
  }

  std::string
  Task::normalize(const std::string& task_name)
  {
    std::string normalized_name;
    std::replace_copy(task_name.begin(), task_name.end(),
                      std::inserter(normalized_name,
                                    normalized_name.begin()),
                      '_', '-');
    return normalized_name;
  }

} // namespace task
