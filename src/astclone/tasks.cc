/**
 ** \file astclone/tasks.cc
 ** \brief Astclone module related tasks' implementation.
 **/

#include <common.hh>

#include <ast/tasks.hh>

#include <astclone/libastclone.hh>
#define DEFINE_TASKS 1
#include <astclone/tasks.hh>
#undef DEFINE_TASKS

namespace astclone
{

  namespace tasks
  {

    void
    clone()
    {
      ast::DecsList* ds = ::astclone::clone(*ast::tasks::the_program);
      if (!ds)
        task_error << misc::error::failure
                   << "Cloning Failed" << std::endl
                   << &misc::error::exit;
      delete ast::tasks::the_program;
      ast::tasks::the_program = ds;
    }

  } // namespace tasks

} // namespace astclone
