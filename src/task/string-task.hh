/**
 ** \file task/string-task.hh
 ** \brief Declare the task::StringTask class.
 **
 */
#ifndef TASK_STRING_TASK_HH
# define TASK_STRING_TASK_HH

# include <task/task.hh>

namespace task
{

  /// A simple Task that sets a String variable.
  class StringTask : public Task
  {
  public:
    StringTask(std::string& var,
               const char* module_name, const char* desc,
               const char* name,
               std::string deps);

  public:
    virtual bool check() const override;
    virtual void execute() const override;

  private:
    std::string& var_;
  };

} //namespace task

#endif // !TASK_STRING_TASK_HH
