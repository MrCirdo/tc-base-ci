/**
 ** \file target/ia32/gas-layout.cc
 ** \brief Print assembly for IA-32 a la GAS
 */

#include <misc/escape.hh>
#include <misc/contract.hh>

#include <temp/label.hh>
#include <tree/all.hh>

#include <assem/libassem.hh>
#include <target/ia32/gas-layout.hh>

namespace target
{
  namespace ia32
  {

    GasLayout& GasLayout::instance()
    {
      static GasLayout unique;
      return unique;
    }

    void
    GasLayout::operator()(const assem::DataFrag& data_frag)
    {
      precondition(postr_);
      const tree::DataFrag& data = data_frag.data_get();
      *postr_
        << "\t.section\t.rodata" << std::endl
        << data.label_get()
        << ":" << std::endl
        << "\t.long " << data.data_get().length() << std::endl
        << "\t.asciz \"" << misc::escape(data.data_get())
        << "\"" << std::endl;
    }

    void
    GasLayout::operator()(const assem::ProcFrag& proc_frag)
    {
      precondition(postr_);
      std::string routine_label = "tc_" + proc_frag.label_get().string_get();
      temp::Label routine_end;

      *postr_
        << "/** Routine: " << proc_frag.name_get() << " */" << std::endl
        << "\t.text"<< std::endl
        << ".globl " << routine_label << std::endl
        << "\t.type\t" << routine_label << ",@function" << std::endl
        << proc_frag.instrs_get()
        << routine_end << ':' << std::endl
        << "\t.size\t" << routine_label << ','
        << routine_end << '-' << routine_label << std::endl;
    }

    void
    GasLayout::operator()(const assem::Fragments& frags)
    {
      precondition(postr_);

      *postr_
        << "/** Tiger final assembler ouput. */" << std::endl
        << std::endl;
      Layout::operator()(frags);
      *postr_
        << "\t.ident\t\"LRDE Tiger Compiler\"" << std::endl;
    }

  } // namespace ia32

} // namespace target
