/**
 ** \file task/task.hxx
 ** \brief Inline methods for task/task.hh.
 */
#ifndef TASK_TASK_HXX
# define TASK_TASK_HXX

# include <task/task.hh>

namespace task
{

  inline
  const char*
  Task::name_get() const
  {
    return name_.c_str();
  }

  inline
  const char*
  Task::module_name_get() const
  {
    return module_name_;
  }

  inline
  int
  Task::key_get() const
  {
    return key_;
  }

  /*------.
  | Arg.  |
  `------*/

  inline
  const char*
  Task::arg_get() const
  {
    return arg_;
  }

  inline
  void
  Task::arg_set(const char* arg) const
  {
    arg_ = arg;
  }


  /*----------.
  | Argname.  |
  `----------*/

  inline
  const char*
  Task::argname_get() const
  {
    return argname_;
  }

  inline
  void
  Task::argname_set(const char* argname)
  {
    argname_ = argname;
  }


  inline
  const char*
  Task::desc_get() const
  {
    return desc_;
  }

  inline
  const Task::deps_type&
  Task::dependencies_get() const
  {
    return dependencies_;
  }

} // namespace task
#endif // !TASK_TASK_HXX
