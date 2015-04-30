/**
 ** \file tree/trees.hh
 ** \brief Intermediate representation: tree_list_type
 **/

#ifndef TREE_TREES_HH
# define TREE_TREES_HH

# include <tree/fwd.hh>

namespace tree
{
  /// Print \a t on \a o.
  std::ostream& operator<<(std::ostream& o, const tree_list_type& t);
}

#endif // !TREE_TREES_HH
