/**
 ** \file task/disjunctive-task.hh
 ** \brief Declare the DisjunctiveTask class.
 **
 */
#ifndef TASK_DISJUNCTIVE_TASK_HH
# define TASK_DISJUNCTIVE_TASK_HH

# include <task/task.hh>

namespace task
{

  /// A Task that make sure that AT LEAST one of its dependencies is
  /// scheduled.
  class DisjunctiveTask : public Task
  {
  public:
    DisjunctiveTask(const char* module_name, const char* desc,
                    const char* name,
                    std::string deps);

  public:
    virtual bool check() const override;
    virtual void execute() const override;
    virtual deps_type
    resolve_dependencies(tasks_list_type& active_tasks) const override;
  };

} //namespace task

#endif // !TASK_DISJUNCTIVE_TASK_HH

