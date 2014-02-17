/**
 ** \file task/function-task.hh
 ** \brief Declare the task::FunctionTask class.
 **
 */
#ifndef TASK_FUNCTION_TASK_HH
# define TASK_FUNCTION_TASK_HH

# include <task/task.hh>

namespace task
{

  /// A simple Task that invokes a callback function.
  class FunctionTask : public Task
  {
  public:
    FunctionTask(void (*callback)(),
                 const char* module_name, const char* desc,
                 const char* name,
                 std::string deps);

  public:
    virtual bool check() const override;
    virtual void execute() const override;

  private:
    void (*execute_)();
  };

} //namespace task

#endif // !TASK_FUNCTION_TASK_HH
