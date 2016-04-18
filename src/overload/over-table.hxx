/**
 ** \file overload/over-table.hxx
 ** \brief Inline methods and template implementations for overload/over-table.hh.
 */

#pragma once

#include <ostream>
#include <overload/over-table.hh>

namespace overload
{

  template <typename T>
  OverTable<T>::OverTable ()
  {
    oversymtab_.emplace_front ();
  }

  template <typename T>
  void    OverTable<T>::put (misc::symbol key, T& value)
  {
    oversymtab_.front ()[key].push_back (&value);
  }

  template <typename T>
  typename OverTable<T>::tlist_type
  OverTable<T>::get (misc::symbol key)
  {
    precondition (!oversymtab_.empty ());
    return oversymtab_.front () [key];
  }

  template <typename T>
  void    OverTable<T>::scope_begin ()
  {
    oversymtab_.push_front (oversymtab_.front ());
  }

  template <typename T>
  void    OverTable<T>::scope_end ()
  {
    precondition (!oversymtab_.empty ());
    oversymtab_.pop_front ();
  }

  template <typename T>
  std::ostream& OverTable<T>::print (std::ostream& ostr) const
  {
    ostr <<"<overTable>\n";
    for (const mmap_type* il : oversymtab_)
      {
        ostr << "<scope>\n";
        for (const typename mmap_type::value_type& im : il)
          ostr << im.first//  << " = " << *im->second
               << std::endl;
        ostr << "</scope>\n";
      }
    return ostr <<"</overTable>\n";
  }

} // namespace type
