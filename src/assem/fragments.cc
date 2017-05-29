/**
 ** \file assem/fragments.cc
 ** \brief Implementation of assem::Fragments.
 */

#include <functional>
#include <misc/contract.hh>

#include <misc/algorithm.hh>
#include <assem/fragment.hh>
#include <assem/fragments.hh>

namespace assem
{

  Fragments::~Fragments()
  {
    misc::deep_clear(*this);
  }


  std::ostream&
  Fragments::print(std::ostream& ostr)
  {
    ostr << "# == Final assembler ouput. == #\n";

    for (const Fragment* frag : *this)
      {
        invariant(frag != nullptr);
        ostr << *frag << std::endl;
      }
    return ostr;
  }

} // namespace assem
