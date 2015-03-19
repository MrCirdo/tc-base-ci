/**
 ** \file overload/liboverload.cc
 ** \brief Define exported type functions.
 */

#include <overload/liboverload.hh>
#include <overload/binder.hh>
#include <overload/type-checker.hh>

namespace overload
{

  std::pair<overfun_bindings_type*, misc::error>
  bind(ast::Ast& tree)
  {
    Binder bind;
    bind(tree);
    if (bind.error_get())
      delete bind.overfun_bindings_get();
    return make_pair(bind.overfun_bindings_get(), bind.error_get());
  }

  misc::error
  types_check(ast::Ast& tree,
              overfun_bindings_type* overfun_bindings)
  {
    TypeChecker type(overfun_bindings);
    type(tree);
    return type.error_get();
  }

} // namespace overload
