/**
 ** \file misc/select-const.hh
 ** \brief Select between a non const or a const type.
 */

#ifndef MISC_SELECT_CONST_HH
# define MISC_SELECT_CONST_HH

namespace misc
{

  /*------------------.
  | const selectors.  |
  `------------------*/

  /// Return \a T constified.
  template <typename T>
  struct constify_traits
  {
    typedef const T type;
  };

  /// Return \a T as is.
  template <typename T>
  struct id_traits
  {
    typedef T type;
  };



  /*------------------.
  | select_iterator.  |
  `------------------*/

  /// The iterator over a non const structure is plain iterator.
  template <typename T>
  struct select_iterator
  {
    typedef typename T::iterator type;
  };

  /// The iterator over a const structure is a const_iterator.
  template <typename T>
  struct select_iterator<const T>
  {
    typedef typename T::const_iterator type;
  };

} //namespace misc

#endif // !MISC_SELECT_CONST_HH
