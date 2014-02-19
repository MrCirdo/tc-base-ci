/**
 ** \file ast/type-dec.hxx
 ** \brief Inline methods of ast::TypeDec.
 */

#ifndef AST_TYPE_DEC_HXX
# define AST_TYPE_DEC_HXX

# include <ast/type-dec.hh>

namespace ast
{


  inline const Ty&
  TypeDec::ty_get() const
  {
    return *ty_;
  }
  inline Ty&
  TypeDec::ty_get()
  {
    return *ty_;
  }


} // namespace ast

#endif // !AST_TYPE_DEC_HXX
