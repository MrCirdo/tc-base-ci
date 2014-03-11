/**
 ** \file overload/over-table.hh
 ** \brief Checking/translating an OverTiger program in a Tiger program.
 */

#ifndef OVERLOAD_OVER_TABLE_HH
# define OVERLOAD_OVER_TABLE_HH

# include <map>
# include <list>

namespace overload
{

  template <typename T>
  class OverTable
  {
  public:
    typedef std::list<T*>                               tlist_type;
    typedef typename tlist_type::const_iterator         const_iterator;
    typedef std::map<const misc::symbol, tlist_type>    mmap_type;
    typedef std::list<mmap_type>                        oversymtab_type;

    typedef std::pair<const_iterator, const_iterator>   range_type;

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

# include <overload/over-table.hxx>

#endif // !OVERLOAD_OVER_TABLE_HH
