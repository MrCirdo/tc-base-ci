/**
 ** \file tree/exp.hh
 ** \brief Intermediate representation: exp.hh
 **/

#ifndef TREE_EXP_HH
# define TREE_EXP_HH

# include <tree/tree.hh>

namespace tree
{

  /** \brief Node that has a value, contrary to \a Stm.
   ** \see tree::Stm.
   */
  class Exp : public Tree
  {
  public:
    virtual ~Exp() = default;
  };

}

#endif // !TREE_EXP_HH
