/**
 ** \file tree/name.hh
 ** \brief Intermediate representation: name.hh
 **/

#ifndef TREE_NAME_HH
# define TREE_NAME_HH

# include <iosfwd>

# include <tree/exp.hh>
# include <tree/label.hh>
# include <temp/label.hh>

namespace tree
{

  class Name : public Exp
  {
  public:
    /// Build a reference to \a label.
    Name(const temp::Label& label);

    /** \name Accessors.
     ** \{ */

    /// Referenced label.
    temp::Label label_get() const;

    /// name_kind.
    virtual kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  private:
    /// Referenced label.
    temp::Label label_;
  };

}

# include <tree/name.hxx>

#endif // !TREE_NAME_HH
