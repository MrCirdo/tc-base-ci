/**
 ** \file tree/temp.hh
 ** \brief Declaration of tree::Temp.
 **/

#ifndef TREE_TEMP_HH
# define TREE_TEMP_HH

# include <iosfwd>

# include <temp/fwd.hh>
# include <tree/exp.hh>
# include <temp/temp.hh>

namespace tree
{

  /// An Exp for a temporary (pseudo register).
  class Temp : public Exp
  {
  public:
    /// Build a node representing the temporary \a temp.
    Temp(const temp::Temp& temp);

    /** \name Accessors.
     ** \{ */

    /// Pseudo register.
    temp::Temp temp_get() const;

    /// Temp kind.
    virtual kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  private:
    /// Pseudo register.
    temp::Temp temp_;
  };

}

# include <tree/temp.hxx>

#endif // !TREE_TEMP_HH
