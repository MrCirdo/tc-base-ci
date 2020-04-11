/**
 ** \file tree/cjump.hxx
 ** \brief Inline implementation of tree::Cjump.
 **/

#pragma once

#include <misc/contract.hh>
#include <temp/label.hh>
#include <tree/cjump.hh>

namespace tree
{
  inline rExp Cjump::left_get() const { return child_get(0).cast<Exp>(); }

  inline rExp Cjump::right_get() const { return child_get(1).cast<Exp>(); }

  inline temp::Label Cjump::label_true_get() const
  {
    const rName name = child_get(2).cast<Name>();
    return name->label_get();
  }

  inline temp::Label Cjump::label_false_get() const
  {
    const rName name = child_get(3).cast<Name>();
    return name->label_get();
  }

  inline void Cjump::label_false_set(const temp::Label& false_label)
  {
    children_.pop_back();
    children_.emplace_back(new Name(false_label));
  }

  inline temp::label_list_type Cjump::labels_get() const
  {
    temp::label_list_type res(label_true_get(), label_false_get());
    return res;
  }

  inline void Cjump::flip()
  {
    precondition(children_.size() == 4);
    rTree iftrue = child_get(2);
    rTree iffalse = child_get(3);
    children_.pop_back();
    children_.pop_back();
    children_.emplace_back(iffalse);
    children_.emplace_back(iftrue);

    static const std::unordered_map<Relop, Relop> relop = {
      {Relop::eq, Relop::ne},   {Relop::ne, Relop::eq},
      {Relop::lt, Relop::ge},   {Relop::gt, Relop::le},
      {Relop::le, Relop::gt},   {Relop::ge, Relop::lt},
      {Relop::ult, Relop::uge}, {Relop::ugt, Relop::ule},
      {Relop::ule, Relop::ugt}, {Relop::uge, Relop::ult}};

    relop_ = relop.at(relop_);
  }

  inline const Cjump::Relop& Cjump::relop_get() const { return relop_; }

} // namespace tree
