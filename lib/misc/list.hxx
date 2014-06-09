/**                                                     -*- C++ -*-
 ** \file misc/list.hxx
 ** \brief Implementation of misc::list.
 */

#ifndef MISC_LIST_HXX
# define MISC_LIST_HXX

# include <algorithm>
# include <ostream>

# include <misc/list.hh>
# include <misc/contract.hh>

namespace misc
{
  template <class T>
  list<T>::list()
  {
  }

  template <class T>
  list<T>::~list()
  {
  }

  template <class T>
  list<T>::list(const T& t1)
  {
    this->push_back(t1);
  }

  template <class T>
  list<T>::list(const T& t1, const T& t2)
  {
    this->push_back(t1);
    this->push_back(t2);
  }

  template <class T>
  list<T>::list(const T& t1, const list<T>& l2)
  {
    this->insert(this->begin(), l2.begin(), l2.end());
    this->push_front(t1);
  }

  template <class T>
  list<T>::list(std::initializer_list<T> l)
  {
    this->insert(this->begin(), l.begin(), l.end());
  }

  template <class T>
  template <class InputIterator>
  list<T>::list(InputIterator f, InputIterator l)
    : super_type(f, l)
  {
  }

  template <class T>
  template <class C>
  list<T>::list(const C& c)
    : super_type(c.begin(), c.end())
  {
  }

  template <class T>
  bool
  list<T>::has(const T& data) const
  {
    return std::find(this->begin(), this->end(), data) != this->end();
  }

  // Concatenation.
  template <class T>
  inline
  list<T>
  list<T>::operator+(const list<T>& s) const
  {
    list<T> res = *this;
    return res += s;
  }

  template <class T>
  inline
  list<T>&
  list<T>::append(const list<T>& s)
  {
    this->insert(this->end(), s.begin(), s.end());
    return *this;
  }

  template <class T>
  inline
  list<T>&
  list<T>::operator+=(const list<T>& s)
  {
    return this->append(s);
  }

  template <class T>
  inline
  list<T>&
  list<T>::operator-=(const T& data)
  {
    precondition(has(data));
    this->erase(std::find(this->begin(), this->end(), data));
    return *this;
  }

  template <class T>
  std::ostream&
  list<T>::dump(std::ostream& ostr) const
  {
    for (typename super_type::const_iterator i = this->begin();
         i != this->end(); ++i)
      ostr << (i == this->begin() ? "" : ", ") << *i;
    return ostr;
  }

  template <class T>
  std::ostream&
  operator<<(std::ostream& ostr, const list<T>& l)
  {
    return l.dump(ostr);
  }

  template <class T>
  bool
  operator%(const T& data, const list<T>& l)
  {
    return l.has(data);
  }

} // namespace misc

#endif // !MISC_LIST_HXX
