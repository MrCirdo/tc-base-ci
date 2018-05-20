/**
 ** \file target/codegen.cc
 ** \brief Implementation of target::Codegen.
 */

#include <misc/contract.hh>
#include <target/codegen.hh>

namespace target
{

  // Generate code.
  assem::Instrs&
  Codegen::codegen(const tree::rStm& stm, frame::Frame& frame)
  {
    frame_ = &frame;
    instrs_.clear();
    assertion(instrs_.empty());
    codegen(stm);
    return instrs_;
  }

} // namespace target
