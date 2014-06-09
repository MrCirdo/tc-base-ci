/**
 ** \file assem/fragments.hh
 ** \brief Fragments of assembly.
 */

#ifndef ASSEM_FRAGMENTS_HH
# define ASSEM_FRAGMENTS_HH

# include <list>
# include <assem/fwd.hh>

namespace assem
{

  /// Abstract a fragment in assembly language.
  class Fragments : public std::list<Fragment*>
  {
  public:
    /// Destroy all the fragments, and reclaim the whole memory.
    virtual ~Fragments();

    /// \brief Issue the \a fragments on \a ostr.
    std::ostream& print(std::ostream& ostr);
  };

  std::ostream&
  operator<<(std::ostream& ostr, const Fragments& fragments);

} // namespace assem

#endif // !ASSEM_FRAGMENTS_HH
