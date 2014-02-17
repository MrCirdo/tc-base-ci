/**
 ** \file misc/list.hh
 ** \brief Declaration of misc::list.
 */

#ifndef MISC_LIST_HH
# define MISC_LIST_HH

# include <iosfwd>
# include <list>

namespace misc
{

  template <class Ident_>
  class list : public std::list<Ident_>
  {
  public:
    /// Super class type.
    typedef std::list<Ident_> super_type;

    /// \name Constructors and destructor.
    /// \{
    /// Build an empty list.
    list();

    /// Build a one-element list.
    list(const Ident_& t1);

    /// Build a two-element list.
    list(const Ident_& t1, const Ident_& t2);

    /// Concat an element and a list.
    list(const Ident_& t1, const list& l2);

    /// Buid a list from 2 iterators.
    template <class InputIterator>
    list(InputIterator f, InputIterator l);

    /// Build a list from another container.
    template <class C> list(const C& c);

    virtual ~list();
    /// \}

    /// \name Content management.
    /// \{
    /// Is \a data part of \a this list?
    bool has(const Ident_& data) const;

    /// Concatenate \a this and \a l.
    list operator+(const list& l) const;

    /// Append \a l into \a this.
    list& append(const list& l);
    /// Append \a l into \a this and return it..
    list& operator+=(const list& l);

    /** \brief Remove \a data from \a this.
        \a data must be part of \a this. */
    list& operator-=(const Ident_& data);
    /// \}

    /// Print the list onto \a ostr.
    virtual std::ostream& dump(std::ostream& ostr) const;

  };

  /// Output \a l onto \a ostr.
  template <class Ident_>
  std::ostream& operator<<(std::ostream& ostr, const list<Ident_>& l);

  /// Shortcut for misc::list::has.
  template <typename Ident_>
  bool operator%(const Ident_& data, const list<Ident_>& l);
}

# include <misc/list.hxx>

#endif // !MISC_LIST_HH
