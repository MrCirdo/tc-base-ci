/**
 ** \file assem/visitor.hh
 ** \brief Allow to visit assembly fragments.
 */

#ifndef ASSEM_VISITOR_HH
# define ASSEM_VISITOR_HH

# include <misc/select-const.hh>
# include <assem/fwd.hh>

namespace assem
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
    /// Visit an assembly procedure fragment.
    virtual void operator()(typename Const<ProcFrag>::type& a);
    /// Visit an assembly data fragment.
    virtual void operator()(typename Const<DataFrag>::type& a);
    /// To enable the use of standard algorithm on containers of pointers.
    template <class E>
    void operator()(E* e);

    /// Visit a list of assembly fragments.
    virtual void operator()(typename Const<Fragments>::type& fs);
  };

  /// Readonly visitor.
  typedef GenVisitor<misc::constify_traits> ConstVisitor;
  /// Read-write visitor.
  typedef GenVisitor<misc::id_traits> Visitor;

} // namespace assem

# include <assem/visitor.hxx>

#endif // !ASSEM_VISITOR_HH
