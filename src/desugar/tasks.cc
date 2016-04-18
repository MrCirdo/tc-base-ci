/**
 ** \file desugar/tasks.cc
 ** \brief Desugar module related tasks' implementation.
 **/

#include <common.hh>

#include <ast/tasks.hh>

#include <astclone/libastclone.hh>
#include <desugar/libdesugar.hh>
#define DEFINE_TASKS 1
#include <desugar/tasks.hh>
#undef DEFINE_TASKS

namespace desugar
{

  namespace tasks
  {

    /*-------------.
    | Desugaring.  |
    `-------------*/

    void
    desugar()
    {
      ast::DecsList* desugared =
        ::desugar::desugar(*ast::tasks::the_program,
                           desugar_for_p,
                           desugar_string_cmp_p);
      std::swap(ast::tasks::the_program, desugared);
      delete desugared;
    }


    void
    raw_desugar()
    {
      ast::DecsList* desugared =
        ::desugar::raw_desugar(*ast::tasks::the_program,
                               desugar_for_p,
                               desugar_string_cmp_p);
      std::swap(ast::tasks::the_program, desugared);
      delete desugared;
    }


    /*-----------------------.
    | Array bounds checking.  |
    `-----------------------*/

    void
    bounds_checks_add()
    {
      astclone::apply(::desugar::bounds_checks_add, ast::tasks::the_program);
    }


    void
    raw_bounds_checks_add()
    {
      astclone::apply(::desugar::raw_bounds_checks_add,
                      ast::tasks::the_program);
    }

  } // namespace tasks

} // namespace desugar
