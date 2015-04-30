/**
 ** \file tree/temp.hxx
 ** \brief Inline methods for tree/temp.hh.
 **/

#ifndef TREE_TEMP_HXX
# define TREE_TEMP_HXX

# include <tree/temp.hh>

namespace tree
{

  inline
  Temp::Temp(const temp::Temp& temp)
    : Exp()
    , temp_(temp)
  {}

  inline temp::Temp
  Temp::temp_get() const
  {
    return temp_;
  }

}

#endif // !TREE_TEMP_HXX
