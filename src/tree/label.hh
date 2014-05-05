/**
 ** \file tree/label.hh
 ** \brief Intermediate representation: label.hh
 **/

#ifndef TREE_LABEL_HH
# define TREE_LABEL_HH

# include <iosfwd>

# include <temp/fwd.hh>
# include <tree/stm.hh>
# include <temp/label.hh>

namespace tree
{

  class Label : public Stm
  {
  public:
    /// Build a node representing the label \a label.
    explicit Label (const temp::Label& label);

    /** \name Accessors.
     ** \{ */

    /// Label represented by the node.
    temp::Label label_get () const;

    /// label_kind.
    virtual kind_tree_type kind_get () const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print (std::ostream& ostr) const override;

    /** \} */

  private:
    /// The label.
    temp::Label label_;
  };

}

# include <tree/label.hxx>

#endif // !TREE_LABEL_HH
