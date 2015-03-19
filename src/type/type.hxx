/**
 ** \file type/type.hxx
 ** \brief Inline methods for type::Type.
 */
#ifndef TYPE_TYPE_HXX
# define TYPE_TYPE_HXX

# include <type/type.hh>
# include <misc/contract.hh>

namespace type
{
  inline std::ostream&
  operator<<(std::ostream& ostr, const Type& t)
  {
    return t.dump(ostr);
  }

  inline bool
  operator==(const Type& lhs, const Type& rhs)
  {
  // FIXME: Some code was deleted here.
  }

  inline bool
  operator!=(const Type& lhs, const Type& rhs)
  {
  // FIXME: Some code was deleted here.
  }

} // namespace type

#endif // !TYPE_TYPE_HXX
