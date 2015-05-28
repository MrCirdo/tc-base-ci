/**
 ** \file assem/move.hh
 ** \brief Specialization of assem::Instr for moves.
 */

#ifndef ASSEM_MOVE_HH
# define ASSEM_MOVE_HH

# include <assem/instr.hh>

namespace assem
{

  class Move : public Instr
  {
  public:
    Move(const std::string& assem,
         const temp::Temp& used_temps,
         const temp::Temp& defd_temps);

    temp::Temp dst_get() const;

    temp::Temp src_get() const;

    temp::Temp use_get() const;

    temp::Temp def_get() const;

    virtual std::ostream& dump(std::ostream& ostr) const override;
  }; // class Move

  // Shorthand.
  using moves_type = std::list<assem::Move*>;
  using const_moves_type = std::list<const assem::Move*>;

} // namespace assem

# include <assem/move.hxx>

#endif // !ASSEM_MOVE_HH
