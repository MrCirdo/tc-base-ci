/**
 ** \file tree/call.hh
 ** \brief Intermediate representation: call.hh
 **/

#ifndef TREE_CALL_HH
# define TREE_CALL_HH

# include <list>
# include <iosfwd>
# include <tree/exp.hh>

namespace tree
{

  class Call : public Exp
  {
  public:
    /** \brief Construct a call to a function.
     **
     ** \param func     Function called
     ** \param args     Arguments of the function, including static link
     **                 if required.
     */
    Call (const rExp& func, const std::list<rExp>& args);

    /** \name Accessors.
     ** \{ */

    /// call_kind.
    virtual kind_tree_type kind_get () const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print (std::ostream&) const override;

    // Lists need a closer.
    virtual std::ostream& dump (std::ostream& ostr) const override;

    /** \} */

  };

}

#endif // !TREE_CALL_HH
