/**
 ** \file temp/temp.hh
 ** \brief Fresh temporaries.
 */

#ifndef TEMP_TEMP_HH
# define TEMP_TEMP_HH

# include <misc/list.hh>
# include <misc/endomap.hh>
# include <temp/identifier.hh>

# ifndef MAYBE_EXTERN
#  define MAYBE_EXTERN extern
# endif

namespace temp
{

  template <typename Tag_>
  struct temp_traits;

  template <>
  struct temp_traits<misc::symbol>
  {
    static const std::string prefix;
    static const int rank;
  };

  template <>
  struct temp_traits<unsigned>
  {
    static const std::string prefix;
    static const int rank;
  };

  /// Anonymous and named Temp.
  typedef Identifier<temp_traits> Temp;

  // Static member specialization declaration.
  //
  // Do not use the `Temp' typedef to make it clear that template<>
  // is required.
  template <> unsigned Identifier<temp_traits>::count_;

  /// Temp Map.
  typedef misc::endo_map<Temp> TempMap;


  // Explicit template instantiation declarations.
  MAYBE_EXTERN template class Identifier<temp_traits>;

  MAYBE_EXTERN template
  std::ostream& operator<<(std::ostream& ostr,
                           const Identifier<temp_traits>& obj);

} // namespace temp

namespace misc
{

  // Explicit template instantiation declarations.
  MAYBE_EXTERN template class endo_map<temp::Temp>;

  MAYBE_EXTERN template
  std::ostream& operator<<(std::ostream& ostr,
                           const map<temp::Temp, temp::Temp>& m);

  MAYBE_EXTERN template class list<temp::Temp>;
  MAYBE_EXTERN template
  list<temp::Temp>::list(misc::set<temp::Temp>::const_iterator f,
                         misc::set<temp::Temp>::const_iterator l);
  MAYBE_EXTERN template
  list<temp::Temp>::list(list<temp::Temp>::const_iterator f,
                         list<temp::Temp>::const_iterator l);
  MAYBE_EXTERN template list<temp::Temp>::list(const misc::set<temp::Temp>& s);
  MAYBE_EXTERN template std::ostream& operator<<(std::ostream& ostr,
                                                 const list<temp::Temp>& l);
  MAYBE_EXTERN template bool operator% (const temp::Temp& t,
                                        const list<temp::Temp>& l);
}

#endif // !TEMP_TEMP_HH
