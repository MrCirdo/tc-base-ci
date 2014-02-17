/**
 ** \file task/task-register.hh
 ** \brief Declare the task::TaskRegister class.
 **
 */

#ifndef TASK_TASK_REGISTER_HH
# define TASK_TASK_REGISTER_HH

# include <iosfwd>
# include <string>
# include <list>
# include <map>

# include <task/fwd.hh>
# include <misc/timer.hh>

namespace task
{

  /** \brief Register Tasks.

  The purpose of the TaskRegister class is to collect tasks
  and organize their execution using their dependencies (like 'make').
  For modeling details, see Design Patterns: singleton.
  */

  class TaskRegister
  {
    // Make it non-copyable.
    TaskRegister(const TaskRegister&) = delete;
    TaskRegister & operator=(const TaskRegister&) = delete;

    /// \name Ctor & dtor.
  private:
    /// Construct a TaskRegister.
    TaskRegister() = default;
  public:
    /// Access to the unique TaskRegister.
    static TaskRegister& instance();

    /** \name Tasks registering.
     ** \{ */
  public:
    /// Register task \a task.
    void register_task(const Task& task);
    /// Register the task \a task_name for execution.
    void enable_task(const std::string& task_name, const char* arg = nullptr);

    /// Return the number of tasks to execute.
    int nb_of_task_to_execute_get();
    /** \} */


    /// \name Task reordering.
  private:
    /** \brief Resolve dependencies between tasks.
     **
     ** Resolve dependencies on tasks registered for execution.
     ** Make a depth first searh of implicit tasks graph,
     ** check cycles and build an ordered list of tasks. */
    void resolve_dependencies(const Task& task);

  public:
    /** \brief Parse \a argv and determine which tasks to execute.
     **
     ** Call 'argp ()'. */
    char* parse_arg(int argc, char* argv[]);


    /** \name Display TaskRegister content.
     ** \{ */
  public:
    /// Display registered Tasks.
    std::ostream& print_task_list(std::ostream& ostr);
    /// Display task graph.
    std::ostream& print_task_graph(std::ostream& ostr);
    /// Display registered Tasks execution order.
    std::ostream& print_task_order(std::ostream& ostr);
    /// }


    /** \name Using registered Tasks.
     ** \{ */
  public:
    /// Execute tasks, checking dependencies.
    void execute();
    /** \} */

    /** \name Time management.
     ** \{ */
  public:
    /// Access to the tasks timer.
    const misc::timer& timer_get() const;
    /** \} */

  public:
    /// Ordered list of tasks.
    typedef std::list<Task const*> tasks_list_type;
    /// Associate an integer key to a task
    typedef std::map<int, Task const*> tasks_by_key_type;
    /// Access to task_keys_ (read-only)
    const tasks_by_key_type& task_keys_get() const;

  private:
    /// Associate a task name to a task
    typedef std::map<const std::string, Task const*> tasks_by_name_type;
    /// 'string to task' map.
    tasks_by_name_type task_list_;

    /// 'key to task' map.
    tasks_by_key_type task_keys_;

    /// 'ordered for execution' tasks list.
    tasks_list_type task_order_;

    /// Tasks timer.
    misc::timer timer_;
  };

} // namespace task

# include <task/task-register.hxx>

#endif // !TASK_TASK_REGISTER_HH
