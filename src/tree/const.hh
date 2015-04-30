/**
 ** \file tree/const.hh
 ** \brief Intermediate representation: const.hh
 **/

#ifndef TREE_CONST_HH
# define TREE_CONST_HH

# include <iosfwd>
# include <tree/exp.hh>

namespace tree
{

  class Const : public Exp
  {
  public:
    /// Build a constant integer value.
    explicit Const(int value);

    /** \name Accessors.
     ** \{ */

    /// Return constant integer value.
    const int& value_get() const;

    /// const_kind.
    virtual kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  private:
    const int value_;
  };

}

# include <tree/const.hxx>

#endif // !TREE_CONST_HH
