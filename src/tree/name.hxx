/**
 ** \file tree/name.hxx
 ** \brief Inline methods for tree/name.hh.
 **/

#ifndef TREE_NAME_HXX
# define TREE_NAME_HXX

# include <tree/name.hh>

namespace tree
{

  inline
  Name::Name(const temp::Label& label)
    : Exp()
    , label_(label)
  {}

  inline temp::Label
  Name::label_get() const
  {
    return label_;
  }

}

#endif // !TREE_NAME_HXX
