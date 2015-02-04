/**
 ** \file  misc/deref.hxx
 ** \brief Inline methods for misc/deref.hh.
 **/

#ifndef MISC_DEREF_HXX
# define MISC_DEREF_HXX

# include <misc/deref.hh>
# include <misc/contract.hh>

namespace misc
{
  template <typename T>
  std::ostream&
  Deref::operator<<(const T* t) const
  {
    return this->ostr_ << *t;
  }

  template <typename T>
  std::ostream&
  Deref::operator<<(T* t) const
  {
    return this->ostr_ << *t;
  }

  template <typename T>
  std::ostream&
  Deref::operator<<(const ref<T>& t) const
  {
    return this->ostr_ << *t;
  }

  template <typename T>
  std::ostream&
  Deref::operator<<(const T& t) const
  {
    return this->ostr_ << t;
  }

  template <typename T>
  std::ostream&
  Deref::operator<<(T& t) const
  {
    return this->ostr_ << t;
  }

  inline
  Deref
  operator<<(std::ostream& ostr, deref_e)
  {
    return Deref(ostr);
  }
}

#endif // !MISC_DEREF_HXX
