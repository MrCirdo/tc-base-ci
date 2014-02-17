/**
 ** \file  misc/deref.hh
 ** \brief Automatically derefencing pointers on ostreams.
 **/

#ifndef MISC_DEREF_HH
# define MISC_DEREF_HH

# include <iosfwd>
# include <misc/ref.hh>

namespace misc
{
  enum deref_e { deref };

  class Deref
  {
  protected:
    Deref(std::ostream&);

  public:
    template <typename T> std::ostream& operator<<(const T* t) const;
    template <typename T> std::ostream& operator<<(T* t) const;
    template <typename T> std::ostream& operator<<(const ref<T>& t) const;
    template <typename T> std::ostream& operator<<(const T& t) const;
    template <typename T> std::ostream& operator<<(T& t) const;

  protected:
    friend Deref operator<<(std::ostream&, deref_e);

    std::ostream& ostr_;
  };

  Deref operator<<(std::ostream& ostr, deref_e);

}

# include <misc/deref.hxx>

#endif // !MISC_DEREF_HH
