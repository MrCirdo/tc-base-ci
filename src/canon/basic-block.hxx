/**
 ** \file canon/basic-block.hxx
 ** \brief Inline methods for canon::BasicBlock.
 */

#pragma once

#include <canon/basic-block.hh>

namespace canon
{

  inline
  BasicBlock::BasicBlock(tree_list_type::iterator begin,
                         tree_list_type::iterator end)
    : trees_(tree_list_type(begin, end))
  {}

  inline const BasicBlock*
  BasicBlock::push_back(const rTree& tree)
  {
    trees_.push_back(tree);
    return this;
  }

  inline BasicBlock::tree_list_type&
  BasicBlock::trees_get()
  {
    return trees_;
  }

  inline std::ostream&
  operator<<(std::ostream& ostr, const BasicBlock& block)
  {
    return block.dump(ostr);
  }

}
