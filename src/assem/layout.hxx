/**
 ** \file assem/layout.hxx
 ** \brief Inline methods for assem/layout.hh.
 */

#ifndef ASSEM_LAYOUT_HXX
# define ASSEM_LAYOUT_HXX

# include <assem/layout.hh>

namespace assem
{

  inline
  Layout::Layout()
    : postr_(nullptr)
  {}

  inline void
  Layout::ostr_set(std::ostream& ostr)
  {
    postr_ = &ostr;
  }

} // namespace assem

#endif // !ASSEM_LAYOUT_HXX
