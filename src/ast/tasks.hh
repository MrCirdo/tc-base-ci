/**
 ** \file ast/tasks.hh
 ** \brief Ast module related tasks.
 */

#ifndef AST_TASKS_HH
# define AST_TASKS_HH

# include <task/libtask.hh>
# include <ast/decs-list.hh>

namespace ast
{

  /// Task for ast.
  namespace tasks
  {
    /// Global root node of abstract syntax tree.
    extern ast::DecsList* the_program;

    TASK_GROUP("2. Abstract Syntax Tree");

    /// Display the abstract syntax tree
    TASK_DECLARE("A|ast-display", "display the AST",
                 ast_display, "parse");

    /// Free the ast (if defined)
    TASK_DECLARE("D|ast-delete", "delete the AST",
                 ast_delete, "parse");
  } // namespace tasks

} // namespace ast

#endif // !AST_TASKS_HH
