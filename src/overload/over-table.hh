/**
 ** \file overload/over-table.hh
 ** \brief Checking/translating an OverTiger program in a Tiger program.
 */

#pragma once

#include <map>
#include <list>

namespace overload
{

  template <typename T>
  class OverTable
  {
  public:
    using tlist_type = std::list<T*>;
    using const_iterator = typename tlist_type::const_iterator;
    using mmap_type = std::map<const misc::symbol, tlist_type>;
    using oversymtab_type = std::list<mmap_type>;

    using range_type = std::pair<const_iterator, const_iterator>;

  public:
    OverTable();

  public:
    void                put(misc::symbol key, T& value);

    tlist_type          get(misc::symbol key);

  public:
    /** \name Scopes.
     ** \{ */
  public:
    /** \brief Open a new scope.
     **
     ** All further type related declarations will be limited to this scope. */
    void scope_begin();

    /** \brief Close the last scope.
     **
     ** Forget everything (ie every type related informations) since the
     ** latest scope_begin (). */
    void scope_end();
    /** \} */


    std::ostream& print(std::ostream& ostr) const;

  protected:
    oversymtab_type     oversymtab_;
  };

} // namespace type

#include <overload/over-table.hxx>
