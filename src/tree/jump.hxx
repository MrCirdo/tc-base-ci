/**
 ** \file tree/jump.hxx
 ** \brief Inline implementation of tree::Jump.
 **/

#ifndef TREE_JUMP_HXX
# define TREE_JUMP_HXX

# include <tree/jump.hh>
# include <tree/name.hh>
# include <temp/label.hh>

namespace tree
{
  inline
  Jump::Jump(const rExp& exp)
    : Stm()
  {
    child_push_back(exp);
  }

  inline rExp
  Jump::exp_get() const
  {
    return child_get(0).cast<Exp>();
  }

  inline
  temp::label_list_type
  Jump::label_get() const
  {
    return { child_get(0).cast<Name>()->label_get() };
  }

}

#endif // !TREE_JUMP_HXX
