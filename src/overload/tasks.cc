/**
 ** \file overload/tasks.cc
 ** \brief Overload module related tasks' implementation.
 */

#include <common.hh>
#include <ast/tasks.hh>

#define DEFINE_TASKS 1
#include <overload/tasks.hh>
#undef DEFINE_TASKS
#include <overload/liboverload.hh>

namespace overload
{

  namespace tasks
  {

    overfun_bindings_type* the_overfun_bindings;

    void
    overfun_bindings_compute()
    {
      std::pair<overfun_bindings_type*, misc::error> result =
        ::overload::bind(*ast::tasks::the_program);
      ::overload::tasks::the_overfun_bindings = result.first;

      task_error << result.second << &misc::error::exit_on_error;
    }

    void
    overfun_types_compute()
    {
      task_error
        << ::overload::types_check(*ast::tasks::the_program,
                                   ::overload::tasks::the_overfun_bindings);
      delete the_overfun_bindings;
      task_error.exit_on_error();
    }

  } // namespace tasks

} // namespace overload
