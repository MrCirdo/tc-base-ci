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
  typedef std::list<assem::Move*> moves_type;
  typedef std::list<const assem::Move*> const_moves_type;

} // namespace assem

# include <assem/move.hxx>

#endif // !ASSEM_MOVE_HH
