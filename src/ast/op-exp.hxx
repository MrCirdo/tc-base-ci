/**
 ** \file ast/op-exp.hxx
 ** \brief Inline methods of ast::OpExp.
 */

#ifndef AST_OP_EXP_HXX
# define AST_OP_EXP_HXX

# include <ast/op-exp.hh>

namespace ast
{


  inline const Exp&
  OpExp::left_get() const
  {
    return *left_;
  }
  inline Exp&
  OpExp::left_get()
  {
    return *left_;
  }

  inline OpExp::Oper
  OpExp::oper_get() const
  {
    return oper_;
  }

  inline const Exp&
  OpExp::right_get() const
  {
    return *right_;
  }
  inline Exp&
  OpExp::right_get()
  {
    return *right_;
  }


} // namespace ast

#endif // !AST_OP_EXP_HXX
