/**
 ** \file tree/visitor.hh
 ** \brief Allow to visit intermediate representation fragments.
 */

#ifndef TREE_VISITOR_HH
# define TREE_VISITOR_HH

# include <misc/select-const.hh>
# include <tree/fwd.hh>

namespace tree
{

  template <template <typename> class Const>
  class GenVisitor
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Destroy an Visitor
    virtual ~GenVisitor();
    /** \} */

  public:
    /// Visit an intermediate representation procedure fragment.
    virtual void operator()(typename Const<ProcFrag>::type& a);
    /// Visit an intermediate representation data fragment.
    virtual void operator()(typename Const<DataFrag>::type& a);
    /// To enable the use of standard algorithm on containers of pointers.
    template <class E> void operator()(E* e);

    /// Visit a list of intermediate representation fragments.
    virtual void operator()(typename Const<Fragments>::type& fs);
  };

  /// Readonly visitor.
  typedef GenVisitor<misc::constify_traits> ConstVisitor;
  /// Read-write visitor.
  typedef GenVisitor<misc::id_traits> Visitor;

} // namespace tree

# include <tree/visitor.hxx>

#endif // !TREE_VISITOR_HH
