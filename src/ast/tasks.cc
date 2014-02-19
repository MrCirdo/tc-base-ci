/**
 ** \file ast/tasks.cc
 ** \brief Ast Tasks implementation.
 */

#include <misc/contract.hh>
#include <ast/libast.hh>
#define DEFINE_TASKS 1
#include <ast/tasks.hh>
#undef DEFINE_TASKS

namespace ast
{

  namespace tasks
  {

    // The abstract syntax tree.
    ast::DecsList* the_program = nullptr;

    void
    ast_display()
    {
      precondition(the_program);
      std::cout << "/* == Abstract Syntax Tree. == */"  << std::endl
                << *the_program << std::endl;
    }

    void
    ast_delete()
    {
      delete the_program;
      the_program = nullptr;
    }

  } // namespace tasks

} // namespace ast
