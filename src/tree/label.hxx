/**
 ** \file tree/label.hxx
 ** \brief Inline methods for tree/label.hh.
 **/

#ifndef TREE_LABEL_HXX
# define TREE_LABEL_HXX

# include <tree/label.hh>

namespace tree
{

  inline
  Label::Label(const temp::Label& label)
    : Stm()
    , label_(label)
  {}

  inline temp::Label
  Label::label_get() const
  {
    return label_;
  }

}

#endif // !TREE_LABEL_HXX
