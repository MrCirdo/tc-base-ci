/**
 ** \file tree/eseq.hh
 ** \brief Intermediate representation: eseq.hh
 **/

#ifndef TREE_ESEQ_HH
# define TREE_ESEQ_HH

# include <iosfwd>
# include <tree/exp.hh>
# include <tree/stm.hh>
# include <tree/seq.hh>

namespace tree
{

  class Eseq : public Exp
  {
  public:
    /** \brief Build a list of expressions.
     **
     ** \param stm      Statement list
     ** \param exp      Last expression
     */
    Eseq(const rStm& stm, const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// Statement list
    rStm stm_get() const;

    /// Last expression
    rExp exp_get() const;

    /// eseq_kind.
    virtual kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print(std::ostream&) const override;
    virtual std::ostream& dump(std::ostream& ostr) const override;

    /** \} */

  };

}

# include <tree/eseq.hxx>

#endif // !TREE_ESEQ_HH
