/**
 ** \file task/task-register.cc
 ** \brief Implementation of task::TaskRegister.
 **
 */

#include <cstring>

#include <algorithm>
#include <map>
#include <stack>
#include <functional>

#include <argp.h>

#include <common.hh>
#include <misc/algorithm.hh>
#include <task/task.hh>
#include <task/disjunctive-task.hh>
#include <task/task-register.hh>

namespace task
{

  // Singleton stuff
  TaskRegister&
  TaskRegister::instance()
  {
    static TaskRegister instance_;
    return instance_;
  }

  // Register this task.
  // FIXME: updating two map is not clean.
  void
  TaskRegister::register_task(const Task& task)
  {
    if (task_list_.find(task.name_get()) != task_list_.end())
      {
        task_error << misc::error::failure
                   << program_name
                   << ": TaskRegister::register_task(" << task.name_get()
                   << "): task name already registered."
                   << std::endl;
        return;
      }
    task_list_[task.name_get()] = &task;
    if (task_keys_.find(task.key_get()) != task_keys_.end())
      {
        task_error << misc::error::failure
                   << program_name
                   << ": TaskRegister::register_task(" << task.name_get()
                   << "): task key " << task.key_get();
        if (std::isprint(task.key_get()))
          task_error << " (-" << static_cast<char>(task.key_get()) << ")";
        task_error << " already registered." << std::endl;
        return;
      }
    task_keys_[task.key_get()] = &task;
  }

  // Request the execution of the task task_name.
  void
  TaskRegister::enable_task(const std::string& task_name,
                            const char* arg)
  {
    if (task_list_.find(task_name) == task_list_.end())
      task_error << misc::error::failure
                 << program_name
                 << ": TaskRegister::enable_task(" << task_name
                 << "): this task has not been registered."
                 << std::endl;
    else
      {
        const Task* task = task_list_.find(task_name)->second;
        task->arg_set(arg);
        task->check();
        resolve_dependencies(*task);
        // FIXME: for efficiency, we should use push_front and replace
        // iterator with reverse_iterator
        // FIXME: for efficiency, resolve_dependency should be called once.
        // FIXME: detect cycle.
        task_order_.push_back(task);
      }
  }

  // Return the number of tasks to execute.
  int
  TaskRegister::nb_of_task_to_execute_get()
  {
    return task_order_.size();
  }

  // Resolve dependencies between tasks.
  void
  TaskRegister::resolve_dependencies(const Task& task)
  {
    tasks_list_type enabled_tasks;

    // Retrieved already active tasks.
    for (const std::string& s : task.dependencies_get())
      if (task_list_.find(s) == task_list_.end())
        {
          task_error << misc::error::failure
                     << program_name
                     << ": TaskRegister::resolve_dependencies(\""
                     << task.name_get()
                     << "\"): unknown task: \"" << s << '"'
                     << std::endl;
        }
      else
        {
          const Task* task_dep = task_list_.find(s)->second;
          if (misc::has(task_order_, task_dep))
            enabled_tasks.push_back(task_dep);
        }

    // Ask the task which dependent tasks should be activated.
    const Task::deps_type dep_tasks = task.resolve_dependencies(enabled_tasks);

    // Activate them.
    for (const std::string& s : dep_tasks)
      {
        if (task_list_.find(s) != task_list_.end())
          if (!misc::has(task_order_, task_list_.find(s)->second))
            enable_task(s);
      }
  }

  // Parse a single option.
  static error_t
  parse_opt(int key, char* arg, argp_state* state)
  {
    switch (key)
      {
      case ARGP_KEY_ARG:
        if (state->arg_num >= 1)
          // Too many arguments.
          argp_usage(state);
        else
          *((char **) state->input) = arg;
        break;
      case ARGP_KEY_END:
        if (state->arg_num < 1)
          // Not enough arguments.
          argp_usage(state);
        break;
      default:
        TaskRegister::tasks_by_key_type::const_iterator it =
          TaskRegister::instance().task_keys_get().find(key);
        // If key is known, register the corresponding task for execution.
        if (it == TaskRegister::instance().task_keys_get().end())
          return ARGP_ERR_UNKNOWN;
        TaskRegister::instance().enable_task(it->second->name_get(), arg);
      }

    return 0;
  }

  /// 'char*' lower-than functor.
  struct char_ptr_less
    : public std::binary_function<const char*, const char*, bool>
  {
    /// Return s1 < s2 (call strcmp).
    bool operator()(const char* s1, const char* s2) const
    {
      return strcmp(s1, s2) < 0;
    }
  };


  char*
  TaskRegister::parse_arg(int argc, char* argv[])
  {
    // Create argp options vector.
    //   Collect each module name.
    typedef std::map<const char*, int, char_ptr_less> indexed_modules_type;
    indexed_modules_type indexed_modules;
    for (const tasks_by_name_type::value_type& i : task_list_)
      indexed_modules[i.second->module_name_get()] = 0;

    // Size is number of modules + number of tasks + 1 (zero-filled
    // last line).
    size_t optsize = indexed_modules.size() + task_list_.size() + 1;
    argp_option tc_options[optsize];
    std::memset(tc_options, 0, optsize * sizeof (argp_option));
    // Fill it with module names.
    unsigned i = 0;
    for (indexed_modules_type::iterator it = indexed_modules.begin();
         it != indexed_modules.end(); ++it, ++i)
      {
        tc_options[i].doc = it->first;
        it->second = i + 1;
        tc_options[i].group = it->second;
      }

    //   Fill it with tasks.
    for (tasks_by_name_type::const_iterator it = task_list_.begin();
         it != task_list_.end(); ++it, ++i)
      {
        tc_options[i].name = it->second->name_get();
        tc_options[i].key = it->second->key_get();
        tc_options[i].doc = it->second->desc_get();
        tc_options[i].arg = it->second->argname_get();
        tc_options[i].group = indexed_modules[it->second->module_name_get()];
      }

    // Give control to argp.
    argp_child children[1] = { {nullptr, 0, nullptr, 0} };
    argp argp =
      {
        tc_options,
        parse_opt,
        program_args_doc, program_doc,
        children,
        nullptr, nullptr
      };
    argp_program_version = program_version;
    argp_program_bug_address = program_bug_address;
    char* input_file;
    argp_parse(&argp, argc, argv, 0, nullptr, &input_file);

    return input_file;
  }


  // Display registered Tasks.
  std::ostream&
  TaskRegister::print_task_list(std::ostream& ostr)
  {
    ostr << "List of registered tasks:" << std::endl;
    for (const tasks_by_name_type::value_type& i : task_list_)
      ostr << "\t* " << i.first << std::endl;
    return ostr << std::endl;
  }

  // Dump task graph.
  std::ostream&
  TaskRegister::print_task_graph(std::ostream& ostr)
  {
    ostr << "/* Task graph */"  << std::endl
         << "digraph Tasks {" << std::endl
         << "  node [shape=box, fontsize=14]" << std::endl
      // Preserve the order of the children.
         << "  graph [ordering=out]" << std::endl;

    for (const tasks_by_name_type::value_type& i : task_list_)
      {
        const Task& task = *i.second;
        if (dynamic_cast <const DisjunctiveTask*>(&task))
          ostr << "  \"" << task.name_get() << "\" [shape=diamond]"
               << std::endl;
        ostr << "  \"" << task.name_get() << "\"";
        if (task.dependencies_get().size())
          {
            ostr << " -> {";
            for (const std::string& s : task.dependencies_get())
              ostr <<  " \"" << s << "\"";
            ostr << " } ";
          }
        ostr << std::endl;
      }

    return ostr << "}" << std::endl;
  }

  // Display registered Tasks execution order.
  std::ostream&
  TaskRegister::print_task_order(std::ostream& ostr)
  {
    ostr << "List of Task Order:" << std::endl;
    for (const Task* t : task_order_)
      ostr << "\t* " << t->name_get() << std::endl;
    return ostr << std::endl;
  }

  const TaskRegister::tasks_by_key_type&
  TaskRegister::task_keys_get() const
  {
    return task_keys_;
  }


  // Execute tasks, checking dependencies.
  void
  TaskRegister::execute()
  {
    // FIXME: should be the only one to call resolve_dependency.
    for (const Task* t : task_order_)
      {
        std::string pref(t->module_name_get());
        if (!pref.empty())
          pref = pref[0] + std::string(": ");
        timer_.push(pref + t->name_get());
        t->execute();
        timer_.pop(pref + t->name_get());
      }
  }

} // namespace task
