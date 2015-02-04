/**
 ** \file task/multiple-string-task.hh
 ** \brief Declaration of task::MultipleStringTask.
 **
 */

#ifndef TASK_MULTIPLE_STRING_TASK_HH
# define TASK_MULTIPLE_STRING_TASK_HH

# include <string>
# include <task/argument-task.hh>

namespace task
{

  /// A simple task that invokes callback function with string argument.
  class MultipleStringTask : public ArgumentTask
  {
  public:
    using callback_type = auto (const std::string&) -> void;

    MultipleStringTask(callback_type& cb,
                       const char* module_name, const char* desc,
                       const char* name,
                       std::string deps);

  public:
    virtual void execute() const override;

  public:
    callback_type& execute_;
  };

} // namespace task

#endif // !TASK_MULTIPLE_STRING_TASK_HH
