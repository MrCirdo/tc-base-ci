/**
 ** \file assem/comment.hh
 ** \brief Specialization of assem::Instr for comments source.
 */

#ifndef ASSEM_COMMENT_HH
# define ASSEM_COMMENT_HH

# include <assem/instr.hh>

namespace assem
{

  class Comment : public Instr
  {
  public:
    Comment(const std::string& comment);

    virtual std::ostream& print(std::ostream& ostr) const;
  }; // class Comment

} // namespace assem

# include <assem/comment.hxx>

#endif // !ASSEM_COMMENT_HH
