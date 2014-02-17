/**
 ** \file task/task.hh
 ** \brief Declare the task::Task class.
 */

#ifndef TASK_TASK_HH
# define TASK_TASK_HH

# include <string>
# include <list>
# include <task/task-register.hh>

namespace task
{

  /** \brief A function bound to a command line option.

  The purpose of the Task class is to abstract the execution of a module
  and the tasks on which its execution depends.  This is an implementation
  of the Command Design Pattern.
  */
  class Task
  {

    /** \name Ctor & dtor. */
    /** \{ */
  public:
    /** \brief Construct a Task.

    \param name      name of this task (used for long option)
    \param module_name     name of the module to which the task belongs.
    \param desc      description of this task
    \param key       the optional short option that enables the task
    \param deps            optional space separated list of task names
    */
    Task(const char* name, const char* module_name, const char* desc,
         int key = 0, const std::string& deps = "");

    /// Destroy this Task.
    virtual ~Task();
    /** \}*/


    /** \name Abstract methods.
     ** \{ */
  public:
    /// Check that the preconditions are verified.
    virtual bool check() const = 0;
    /// Execute this task.
    virtual void execute() const = 0;
    /** \} */

    typedef TaskRegister::tasks_list_type tasks_list_type;

    typedef std::list<std::string> deps_type;

    virtual deps_type
    resolve_dependencies(tasks_list_type& active_tasks) const;


    /** \name Accessors.
     ** \{ */
  public:
    /** Access to 'name'.

    'const char*' is preferred to 'std::string' because TaskRegister
    calls C functions, that expect 'const char*'.
    The use of 'std::string::c_str()' is so forbidden and a call to
    'strdup(std::string::c_str())' would implies dummy memory leaks. */
    const char* name_get() const;

    /// Access to 'module_name'.
    const char* module_name_get() const;

    /// Access to 'key'.
    int key_get() const;

    /// Access to 'desc'.
    const char* desc_get() const;

    /// The argument name.
    const char* argname_get() const;
    void argname_set(const char*);

    /// The argument.
    void arg_set(const char* arg) const;
    const char* arg_get() const;

    /// Access to tasks dependencies.
    const deps_type& dependencies_get() const;

    /** \} */

  public:
    /// Display dependencies of this task .
    void print_dependencies() const;

  public:
    /// Normalize the name of a task.
    static std::string normalize(const std::string& task_name);

  protected:
    /// Task name.
    std::string name_;
    /// Module name to which the task belongs.
    const char* module_name_;
    /** \brief The integer key provided by the this task to the option parser.
     **
     ** From 'argp ()':
     ** "If key has a value that is a printable ASCII character
     **  (i.e., isascii (key) is true), it also specifies a short option
     ** '-char' where char is the ASCII character with the code key" */
    int key_;
    /// A short description of this task (displayed in program usage).
    const char* desc_;
    /// The name of the argument to display in the --help message.
    const char* argname_;
    /// The actual argument value.
    mutable const char* arg_;
    /// Contains the name of the tasks on which this one depends.
    deps_type dependencies_;
  };

} // namespace task
# include <task/task.hxx>

#endif // !TASK_TASK_HH
