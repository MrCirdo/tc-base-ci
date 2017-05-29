/**
 ** \file assem/layout.cc
 ** \brief Implementation for assem/layout.hh.
 */

#include <assem/layout.hh>
#include <assem/fragment.hh>
#include <assem/fragments.hh>

namespace assem
{
  void
  Layout::operator()(const Fragments& frags)
  {
    precondition(postr_);
    for (Fragments::const_iterator i = frags.begin(); i != frags.end(); ++i)
      {
        if (i != frags.begin())
          *postr_ << std::endl;
        invariant(*i);
        (*i)->accept(*this);
      }
  }
} // namespace assem
