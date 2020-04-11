/**
 ** \file tree/binop.cc
 ** \brief Implementation for tree/binop.hh.
 **/

#include <ostream>

#include <tree/binop.hh>

namespace tree
{
  Binop::Binop(const Oper oper, const rExp& left, const rExp& right)
    : Exp()
    , oper_(oper)
  {
    child_emplace_back(left);
    child_emplace_back(right);
  }

  std::ostream& Binop::tag_print(std::ostream& ostr) const
  {
    ostr << "binop ";

    static const std::unordered_map<Oper, std::string> oper = {
      {Oper::add, "add"},         {Oper::sub, "sub"},
      {Oper::mul, "mul"},         {Oper::div, "div"},
      {Oper::logic_and, "and"},   {Oper::logic_or, "or"},
      {Oper::lshift, "lshft"},    {Oper::rshift, "rshift"},
      {Oper::arshift, "arshift"}, {Oper::logic_xor, "xor"}};

    return ostr << oper.at(oper_);
  }

  Tree::kind_tree_type Binop::kind_get() const
  {
    return kind_tree_type::binop_kind;
  }

} // namespace tree
