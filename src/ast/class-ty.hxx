/**
 ** \file ast/class-ty.hxx
 ** \brief Inline methods of ast::ClassTy.
 */

#ifndef AST_CLASS_TY_HXX
# define AST_CLASS_TY_HXX

# include <ast/class-ty.hh>

namespace ast
{


  inline const NameTy&
  ClassTy::super_get() const
  {
    return *super_;
  }
  inline NameTy&
  ClassTy::super_get()
  {
    return *super_;
  }

  inline const DecsList&
  ClassTy::decs_get() const
  {
    return *decs_;
  }
  inline DecsList&
  ClassTy::decs_get()
  {
    return *decs_;
  }


} // namespace ast

#endif // !AST_CLASS_TY_HXX
