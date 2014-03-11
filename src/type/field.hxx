/**
 ** \file type/field.hxx
 ** \brief Inline methods for type::Field.
 */
#ifndef TYPE_FIELD_HXX
# define TYPE_FIELD_HXX

# include <type/field.hh>
# include <misc/contract.hh>

namespace type
{
  inline
  Field::Field(misc::symbol name, const Type& type)
    : name_(name)
    , type_(type)
  {}

  inline misc::symbol
  Field::name_get() const
  {
    return name_;
  }

  inline const Type&
  Field::type_get() const
  {
    return type_;
  }

  inline std::ostream&
  operator<<(std::ostream& ostr, const Field& f)
  {
    return f.dump(ostr);
  }

} // namespace type

#endif // !TYPE_FIELD_HXX
