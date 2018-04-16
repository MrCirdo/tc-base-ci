/**
 ** \file tree/cjump.cc
 ** \brief Implementation of tree::Cjump.
 **/

#include <ostream>

#include <tree/cjump.hh>

namespace tree
{

  Cjump::Cjump(Relop relop,
               const rExp& left, const rExp& right,
               const rName& iftrue, const rName& iffalse)
    : Stm()
    , relop_(relop)
  {
    child_emplace_back(left);
    child_emplace_back(right);
    child_emplace_back(iftrue);
    child_emplace_back(iffalse);
  }

  std::ostream&
  Cjump::tag_print(std::ostream& ostr) const
  {
    ostr << "cjump " << relop_;
    return ostr;
  }

  Tree::kind_tree_type
  Cjump::kind_get() const
  {
    return kind_tree_type::cjump_kind;
  }

  Cjump::Relop
  symmetrize(const Cjump::Relop& r)
  {
    std::map<Cjump::Relop, Cjump::Relop> relop =
    {
      {Cjump::Relop::eq, Cjump::Relop::eq},
      {Cjump::Relop::ne, Cjump::Relop::ne},
      {Cjump::Relop::lt, Cjump::Relop::gt},
      {Cjump::Relop::gt, Cjump::Relop::lt},
      {Cjump::Relop::le, Cjump::Relop::ge},
      {Cjump::Relop::ge, Cjump::Relop::le},
      {Cjump::Relop::ult, Cjump::Relop::ugt},
      {Cjump::Relop::ugt, Cjump::Relop::ult},
      {Cjump::Relop::ule, Cjump::Relop::uge},
      {Cjump::Relop::uge, Cjump::Relop::ule}
    };

    auto relop_it = relop.find(r);
    if (relop_it == relop.end())
      die("Should not be here.");
    else
      return relop_it->second;
  }

  std::ostream&
  operator<<(std::ostream& ostr, const Cjump::Relop& r)
  {
    std::map<Cjump::Relop, std::string> relop =
    {
      {Cjump::Relop::eq, "eq"},   {Cjump::Relop::ne, "ne"},
      {Cjump::Relop::lt, "lt"},   {Cjump::Relop::gt, "gt"},
      {Cjump::Relop::le, "le"},   {Cjump::Relop::ge, "ge"},
      {Cjump::Relop::ult, "ult"}, {Cjump::Relop::ugt, "ugt"},
      {Cjump::Relop::ule, "ule"}, {Cjump::Relop::uge, "uge"}
    };

    return ostr << relop.at(r);
  }

} // namespace tree
