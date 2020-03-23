/**
 ** \file inlining/pruner.cc
 ** \brief Implementation of inlining::Pruner.
 */

#include <inlining/pruner.hh>
#include <range/v3/algorithm/remove_if.hpp>

namespace inlining
{
  using namespace ast;

  ast::FunctionDecs* Pruner::prune(ast::FunctionDecs& e)
  {
    func_vect* function_decs = &e.decs_get();

    while (true)
      {
        auto it = ranges::remove_if(
          *function_decs,
          [&](ast::FunctionDec* func_dec) {
            if (!func_dec->body_get() || func_dec->name_get() == "_main")
              return false;
            else
              return called_functions_[func_dec->name_get()] == 0;
          });

        if (it == function_decs->end())
          break;
        function_decs->erase(it, function_decs->end());
      }

    return new FunctionDecs(e.location_get(), function_decs);
  }

  // FIXME: Some code was deleted here.

} // namespace inlining
