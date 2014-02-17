/**
 ** \file task/boolean-task.hh
 ** \brief Declare the task::BooleanTask class.
 **
 */
#ifndef TASK_BOOLEAN_TASK_HH
# define TASK_BOOLEAN_TASK_HH

# include <task/task.hh>

namespace task
{

  /// A simple Task that sets a Boolean variable to true.
  class BooleanTask : public Task
  {
  public:
    BooleanTask(bool& flag,
                const char* module_name, const char* desc,
                const char* name,
                std::string deps);

  public:
    virtual bool check() const override;
    virtual void execute() const override;

  private:
    bool& flag_;
  };

} // namespace task

#endif // !TASK_BOOLEAN_TASK_HH
