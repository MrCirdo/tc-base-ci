/**
 ** \file target/mips/spim-layout.cc
 ** \brief Abstract a fragment's layout.
 */

#include <misc/contract.hh>
#include <misc/escape.hh>

#include <tree/all.hh>

#include <assem/libassem.hh>
#include <target/mips/spim-layout.hh>

namespace target
{
  namespace mips
  {

    SpimLayout&
    SpimLayout::instance()
    {
      static SpimLayout unique;
      return unique;
    }

    void
    SpimLayout::operator()(const assem::DataFrag& data_frag)
    {
      precondition(postr_);
      const tree::DataFrag& data = data_frag.data_get();
      *postr_
        << ".data" << std::endl
        << data.label_get()
        << ":" << std::endl
        << "\t.word " << data.data_get().length() << std::endl
        << "\t.asciiz \"" << misc::escape(data.data_get())
        << "\"" << std::endl
        << ".text" << std::endl;
    }

    void
    SpimLayout::operator()(const assem::ProcFrag& proc_frag)
    {
      precondition(postr_);
      *postr_
        << "# Routine: " << proc_frag.name_get() << std::endl
        << proc_frag.instrs_get();
    }

    void
    SpimLayout::operator()(const assem::Fragments& frags)
    {
      precondition(postr_);
      *postr_ << "# == Final assembler ouput. == #" << std::endl;
      Layout::operator()(frags);
    }

  } // namespace mips

} // namespace target
