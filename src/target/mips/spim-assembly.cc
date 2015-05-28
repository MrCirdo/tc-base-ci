/**
 ** \file target/mips/spim-assembly.cc
 ** \brief Implementation of target::mips::SpimAssembly.
 */

#include <string>

#include <misc/contract.hh>
#include <assem/libassem.hh>
#include <target/mips/spim-layout.hh>
#include <target/mips/spim-assembly.hh>

namespace target
{
  namespace mips
  {
    using Ts = temp::temp_list_type;
    using Ls = temp::label_list_type;

    SpimAssembly::SpimAssembly()
      : Assembly(SpimLayout::instance())
    {}

    // ----------------------- //
    // Arithmetic operations.  //
    // ----------------------- //

    std::string
    SpimAssembly::binop_inst(const tree::Binop::Oper& op) const
    {
  // FIXME: Some code was deleted here.
    }

    assem::Instrs
    SpimAssembly::binop_build(const tree::Binop::Oper& op,
                              const temp::Temp& left,
                              const temp::Temp& right,
                              const temp::Temp& dst) const
    {
  // FIXME: Some code was deleted here.
    }


    assem::Instrs
    SpimAssembly::binop_build(const tree::Binop::Oper& op,
                              const temp::Temp& left,
                              int right,
                              const temp::Temp& dst) const
    {
  // FIXME: Some code was deleted here.
    }

    assem::Instrs
    SpimAssembly::binop_build(const tree::Binop::Oper& op,
                              int left,
                              const temp::Temp& right,
                              const temp::Temp& res) const
    {
      return binop_build(op, right, left, res);
    }

    // ----------------- //
    // Move operations.  //
    // ----------------- //

    assem::Instrs
    SpimAssembly::move_build(const temp::Temp& src,
                             const temp::Temp& dst) const
    {
  // FIXME: Some code was deleted here.
    }

    assem::Instrs
    SpimAssembly::move_build(int immediate, const temp::Temp& dst) const
    {
      std::string opcode = "li\t'd, " +
        std::to_string(immediate);
      return { new assem::Oper(opcode, Ts(), Ts(dst)) };
    }

    assem::Instrs
    SpimAssembly::move_build(const temp::Label& label,
                             const temp::Temp& dst) const
    {
      return { new assem::Oper("la\t'd, " + label.string_get(),
                                Ts(), Ts(dst)) };
    }


    // ----------------- //
    // Load operations.  //
    // ----------------- //

    assem::Instrs
    SpimAssembly::load_build(const temp::Temp& base,
                             int offset,
                             const temp::Temp& dst) const
    {
  // FIXME: Some code was deleted here.
    }

    assem::Instrs
    SpimAssembly::load_build(const temp::Temp& base,
                             const temp::Temp& dst) const
    {
      return load_build(base, 0, dst);
    }

    assem::Instrs
    SpimAssembly::load_build(int absolute,
                             const temp::Temp& dst) const
    {
      std::string opcode = "lw\t'd, "
        + std::to_string(absolute);
      return { new assem::Oper(opcode, Ts(), Ts(dst)) };
    }


    // ------------------ //
    // Store operations.  //
    // ------------------ //

    assem::Instrs
    SpimAssembly::store_build(const temp::Temp& src,
                              const temp::Temp& base,
                              int offset) const
    {
  // FIXME: Some code was deleted here.
    }

    assem::Instrs
    SpimAssembly::store_build(const temp::Temp& src,
                              int absolute) const
    {
      std::string opcode = "sw\t's, "
        + std::to_string(absolute);
      return { new assem::Oper(opcode, Ts(src), Ts()) };
    }

    // Label.
    assem::Instrs
    SpimAssembly::label_build(const temp::Label& label) const
    {
      return { new assem::Label(label.string_get() + ":", label) };
    }

    // ------------------ //
    // Conditional jump.  //
    // ------------------ //

    std::string
    SpimAssembly::cjump_inst(const tree::Cjump::Relop& op) const
    {
  // FIXME: Some code was deleted here.
    }

    assem::Instrs
    SpimAssembly::cjump_build(const tree::Cjump::Relop& op,
                              const temp::Temp& left,
                              const temp::Temp& right,
                              const temp::Label& label_true,
                              const temp::Label& label_false) const
    {
  // FIXME: Some code was deleted here.
    }

    assem::Instrs
    SpimAssembly::cjump_build(const tree::Cjump::Relop& op,
                              const temp::Temp& left,
                              int right,
                              const temp::Label& label_true,
                              const temp::Label& label_false) const
    {
  // FIXME: Some code was deleted here.
    }

    // -------------------- //
    // Unconditional jump.  //
    // -------------------- //

    assem::Instrs
    SpimAssembly::jump_build(const temp::Label& label) const
    {
      return { new assem::Oper("j\t'j", Ts(), Ts(), Ls(label)) };
    }

    // Function.

    assem::Instrs
    SpimAssembly::call_build(const temp::Label& label,
                             const temp::temp_list_type& args,
                             const temp::temp_list_type& dst) const
    {
      return { new assem::Oper("jal\t" "tc_" + label.string_get(),
                               args, dst) };
    }

    assem::Instrs
    SpimAssembly::ret_build(const temp::Temp& ret) const
    {
      return { new assem::Oper("jr\t's", Ts(ret), Ts()) };
    }

  } // namespace mips

} // namespace target
