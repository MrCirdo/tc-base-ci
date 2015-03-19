/**
 ** \file type/named.hxx
 ** \brief Inline methods for type::Named.
 */
#ifndef TYPE_NAMED_HXX
# define TYPE_NAMED_HXX

# include <type/named.hh>
# include <misc/contract.hh>

namespace type
{

  inline
  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  inline
  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
  {
    type_set(type);
  }

  inline const Type*
  Named::type_get() const
  {
    return type_;
  }

  inline void
  Named::type_set(const Type* type)
  {
    type_ = type;
  }

  inline void
  Named::type_set(const Type* type) const
  {
    type_ = type;
  }

  inline misc::symbol
  Named::name_get() const
  {
    return name_;
  }

  inline void
  Named::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline const Type&
  Named::actual() const
  {
  // FIXME: Some code was deleted here.
  }

} // namespace type

#endif // !TYPE_NAMED_HXX
