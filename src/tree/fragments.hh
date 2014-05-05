/**
 ** \file tree/fragments.hh
 ** \brief Declaration of tree::Fragments.
 **/

#ifndef TREE_FRAGMENTS_HH
# define TREE_FRAGMENTS_HH

# include <list>
# include <tree/fwd.hh>

namespace tree
{

  /// Fragments: Fragment list.
  class Fragments : public std::list<tree::Fragment*>
  {
  public:
    typedef std::list<tree::Fragment*> super_type;

    // Inherit constructors from base class.
    using super_type::super_type;

    virtual ~Fragments ();
  };

  /// Report \a fragments on \a ostr.
  std::ostream& operator<< (std::ostream& o, const Fragments& f);

} // namespace tree

#endif // !TREE_FRAGMENTS_HH
