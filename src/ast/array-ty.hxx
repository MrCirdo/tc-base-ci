/**
 ** \file ast/array-ty.hxx
 ** \brief Inline methods of ast::ArrayTy.
 */

#ifndef AST_ARRAY_TY_HXX
# define AST_ARRAY_TY_HXX

# include <ast/array-ty.hh>

namespace ast
{


  inline const NameTy&
  ArrayTy::base_type_get() const
  {
    return *base_type_;
  }
  inline NameTy&
  ArrayTy::base_type_get()
  {
    return *base_type_;
  }


} // namespace ast

#endif // !AST_ARRAY_TY_HXX
