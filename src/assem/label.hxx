/**
 ** \file assem/label.hxx
 ** \brief Specialization of assem::Instr for labels.
 */

#ifndef ASSEM_LABEL_HXX
# define ASSEM_LABEL_HXX

# include <assem/label.hh>

namespace assem
{

  inline
  Label::Label(const std::string& assem,
               const temp::Label& label)
    : Instr(assem)
    , label_(label)
  {
  }

  inline
  temp::Label
  Label::label_get() const
  {
    return label_;
  }

} // namespace assem

#endif // !ASSEM_LABEL_HXX
