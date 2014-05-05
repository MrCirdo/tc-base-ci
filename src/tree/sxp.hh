/**
 ** \file tree/sxp.hh
 ** \brief Intermediate representation: sxp.hh
 **/

#ifndef TREE_SXP_HH
# define TREE_SXP_HH

# include <iosfwd>
# include <tree/stm.hh>
# include <tree/exp.hh>

namespace tree
{
  /** \brief An expression which value is discarded.
   **
   ** Sxp is named EXP by A. Appel, but there are already too many Exp in
   ** this compiler.
   */
  class Sxp : public Stm
  {
  public:
    Sxp (const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// Expression.
    rExp exp_get () const;

    /// sxp_kind.
    virtual kind_tree_type kind_get () const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print (std::ostream& ostr) const override;

    /** \} */

  };

}

# include <tree/sxp.hxx>

#endif // !TREE_SXP_HH
