/**
 ** \file task/multiple-string-task.hh
 ** \brief Declaration of task::MultipleStringTask.
 **
 */

#ifndef TASK_MULTIPLE_STRING_TASK_HH
# define TASK_MULTIPLE_STRING_TASK_HH

# include <string>
# include <task/task.hh>

namespace task
{

  /// A simple task that invokes callback function with string argument.
  class MultipleStringTask : public Task
  {
  public:
    typedef void (callback_type)(const std::string&);

    MultipleStringTask(callback_type& cb,
                       const char* module_name, const char* desc,
                       const char* name,
                       std::string deps);

  public:
    virtual bool check() const override;
    virtual void execute() const override;

  public:
    callback_type& execute_;
  };

} // namespace task


#endif // !TASK_MULTIPLE_STRING_TASK_HH
