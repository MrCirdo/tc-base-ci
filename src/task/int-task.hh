/**
 ** \file task/int-task.hh
 ** \brief Declare the IntTask class.
 **
 */
#ifndef TASK_INT_TASK_HH
# define TASK_INT_TASK_HH

# include <task/task.hh>

namespace task
{

  /// A simple Task that sets an Int variable.
  class IntTask : public Task
  {
  public:
    IntTask(int& var, int min, int max,
            const char* module_name, const char* desc,
            const char* name,
            std::string deps);

  public:
    virtual bool check() const override;
    virtual void execute() const override;

  private:
    int& var_;
    int min_;
    int max_;
  };

} //namespace task

#endif // !TASK_INT_TASK_HH
