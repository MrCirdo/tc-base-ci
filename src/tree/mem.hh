/**
 ** \file tree/mem.hh
 ** \brief Intermediate representation: mem.hh
 **/

#ifndef TREE_MEM_HH
# define TREE_MEM_HH

# include <iosfwd>
# include <tree/exp.hh>

namespace tree
{

  /** \brief Memory indirection.
   **
   ** Allow the access of the memory at a given address.
   */
  class Mem : public Exp
  {
  public:
    /** \brief Construct a memory indirection.
     **
     ** \param exp      Expression of accessed address.
     */
    Mem (const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// Accessed address.
    rExp exp_get () const;
    void exp_set (const rExp& exp);

    /// mem_kind.
    virtual kind_tree_type kind_get () const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print (std::ostream& ostr) const override;

    /** \} */

  };

}

# include <tree/mem.hxx>

#endif // !TREE_MEM_HH
