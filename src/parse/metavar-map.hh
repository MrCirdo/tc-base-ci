/**
 ** \file parse/metavar-map.hh
 ** \brief Declaration of parse::MetavarMap.
 */

#ifndef PARSE_METAVAR_MAP_HH
# define PARSE_METAVAR_MAP_HH

# include <string>
# include <misc/map.hh>

namespace parse
{

  /// A generic map of metavariables.
  template <typename Data>
  class MetavarMap
  {
  public:
    /// Build a map of metavariables of kind \a name.
    MetavarMap(const std::string& name);
    virtual ~MetavarMap();

    /// Generate a (concrete syntax) Tiger statement for metavariable
    /// number \a key (of kind \p Data).
    std::string show(unsigned key);

  protected:
    /// Append a metavariable to the map.
    virtual std::string append_(unsigned& key, Data* data);
    /// Extract a metavariable.
    virtual Data* take_(unsigned key);

    /// Name of the kind of variable.
    const std::string name_;
    /// Metavariables.
    typedef misc::map<unsigned, Data*> map_type;
    map_type map_;
  };

}

# include <parse/metavar-map.hxx>

#endif // !PARSE_METAVAR_MAP_HH
