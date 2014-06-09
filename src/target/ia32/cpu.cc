/**
 ** \file target/ia32/cpu.cc
 ** \brief Implementation for target/ia32/cpu.hh.
 */

#include <misc/contract.hh>
#include <temp/temp.hh>

#include <target/ia32/cpu.hh>

namespace target
{
  namespace ia32
  {

    Cpu::Cpu()
    {
      // General registers.
      caller_save_reg("ebx");
      caller_save_reg("ecx");
      caller_save_reg("edx");
      caller_save_reg("esi");
      caller_save_reg("edi");

      special_reg(fp_reg());
      special_reg(sp_reg());
      special_reg(result_reg());

      (*tempmap_)["fp"] = fp_reg();
      (*tempmap_)["rv"] = result_reg();
    }


    size_t
    Cpu::word_size_get() const
    {
      return 4;
    }

    const temp::Temp&
    Cpu::fp_reg() const
    {
      static const temp::Temp fp("ebp");
      return fp;
    }

    const temp::Temp&
    Cpu::sp_reg() const
    {
      static const temp::Temp sp("esp");
      return sp;
    }

    const temp::Temp&
    Cpu::result_reg() const
    {
      static const temp::Temp result("eax");
      return result;
    }

  } // namespace ia32
} // namespace target
