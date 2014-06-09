/**
 ** \file tree/seq.hh
 ** \brief Intermediate representation: seq.hh
 **/

#ifndef TREE_SEQ_HH
# define TREE_SEQ_HH

# include <iosfwd>
# include <tree/stm.hh>

namespace tree
{

  class Seq : public Stm
  {

  public:
    /** \name Constructors.
     ** \{ */

    /// Construct using \a children as child statement list.
    Seq(const tree_list_type& children);

    /// Construct a statement list of two statements, \a left and \a right.
    Seq(const rStm& left, const rStm& right);

    /// Construct a statement list of one statement, \a left.
    Seq(const rStm& left);

    /// Construct from an initializer list of statements, \a l.
    Seq(std::initializer_list<rStm> l);

    /// Construct an empty statement list.
    Seq() = default;

    /** \} */

    /** \name Accessors.
     ** \{ */

    /// seq_kind.
    virtual kind_tree_type kind_get() const override;

    /** \} */

    /// Append a statement to the statement list.
    void push_back(const rStm& stm);

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print(std::ostream&) const override;
    virtual std::ostream& dump(std::ostream& ostr) const override;

    /** \} */

  };

}

# include <tree/seq.hxx>

#endif // !TREE_SEQ_HH
