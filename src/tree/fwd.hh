/**
 ** \file tree/fwd.hh
 ** \brief Intermediate representation: all the forward declarations.
 **/

#ifndef TREE_FWD_HH
# define TREE_FWD_HH

# include <list>

# include <misc/fwd.hh>
# include <misc/ref.hh>

namespace tree
{
#define DECLARE(What)                           \
  class What;                                   \
  typedef misc::ref< What > r ## What;

  DECLARE(Tree)
  DECLARE(Binop)
  DECLARE(Call)
  DECLARE(Cjump)
  DECLARE(Const)
  DECLARE(Eseq)
  DECLARE(Exp)
  DECLARE(Jump)
  DECLARE(Label)
  DECLARE(Mem)
  DECLARE(Move)
  DECLARE(Name)
  DECLARE(Seq)
  DECLARE(Stm)
  DECLARE(Sxp)
  DECLARE(Temp)

#undef DECLARE

  // Arguably we could include this typedef in the class Tree.
  typedef std::list<rTree> tree_list_type;

  // From fragment.hh.
  class Fragment;
  class ProcFrag;
  class DataFrag;

  // From fragments.hh.
  class Fragments;

  // From visitor.hh.
  template <template <typename> class Const>
  class GenVisitor;
  // FIXME: Ought to be _type.
  typedef GenVisitor<misc::constify_traits> ConstVisitor;
  typedef GenVisitor<misc::id_traits> Visitor;

}

#endif // !TREE_FWD_HH
