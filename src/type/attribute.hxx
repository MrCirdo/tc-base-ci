/**
 ** \file type/attribute.hxx
 ** \brief Inline methods for type::Attribute.
 */
#ifndef TYPE_ATTRIBUTE_HXX
# define TYPE_ATTRIBUTE_HXX

namespace type
{

  inline
  Attribute::Attribute(const ast::VarDec* def)
    : def_(def)
  {}

  inline
  misc::symbol
  Attribute::name_get() const
  {
    return def_->name_get();
  }

  inline
  const Type&
  Attribute::type_get() const
  {
    return *def_->type_get();
  }

  inline
  const ast::VarDec*
  Attribute::def_get() const
  {
    return def_;
  }

  inline
  void
  Attribute::def_set(const ast::VarDec* def)
  {
    def_ = def;
  }

  inline
  std::ostream&
  operator<<(std::ostream& ostr, const Attribute& a)
  {
    return a.dump(ostr);
  }

} // namespace type

#endif // !TYPE_ATTRIBUTE_HXX
