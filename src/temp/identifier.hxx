/**                                                             -*- C++ -*-
 ** \file temp/identifier.hxx
 ** \brief Implementation of Identifier & TaggedIdentifier templates.
 */

#ifndef TEMP_IDENTIFIER_HXX
# define TEMP_IDENTIFIER_HXX

# include <cstdlib>

# include <sstream>
# include <iostream>

# include <boost/variant.hpp>

# include <misc/contract.hh>
# include <temp/identifier.hh>

namespace temp
{

  /*-------------.
  | Identifier.  |
  `-------------*/

  template <template <typename Tag_> class Traits_>
  const misc::xalloc<typename Identifier<Traits_>::map_type*>
  Identifier<Traits_>::map;

  template <template <typename Tag_> class Traits_>
  std::ostream&
  operator<<(std::ostream& ostr, const Identifier<Traits_>& obj)
  {
    typename Identifier<Traits_>::map_type* m =
      Identifier<Traits_>::map(ostr);
    if (m)
      return (*m)(obj).dump(ostr);
    else
      return obj.dump(ostr);
  }


  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>::Identifier()
    : value_(count_)
    , prefix_(&Traits_<unsigned>::prefix)
    , rank_(Traits_<unsigned>::rank)
  {
    ++count_;
  }

  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>::Identifier(const misc::symbol& sym)
    : value_(sym)
    , prefix_(&Traits_<misc::symbol>::prefix)
    , rank_(Traits_<misc::symbol>::rank)
  {
  }

  // FIXME: Some code was deleted here.


  /*------------------.
  | Variant visitor.  |
  `------------------*/

  // FIXME: Some code was deleted here.

} // namespace temp

#endif // !TEMP_IDENTIFIER_HXX
