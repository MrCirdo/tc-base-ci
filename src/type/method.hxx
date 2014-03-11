/**
 ** \file type/method.hxx
 ** \brief Inline methods for type::Method.
 */
#ifndef TYPE_METHOD_HXX
# define TYPE_METHOD_HXX

namespace type
{

  inline misc::symbol
  Method::name_get() const
  {
    return name_;
  }

  inline const Class*
  Method::owner_get() const
  {
    return owner_;
  }

  inline const ast::MethodDec*
  Method::def_get() const
  {
    return def_;
  }

  inline ast::MethodDec*
  Method::def_get()
  {
    return def_;
  }

  inline void
  Method::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline void
  Method::def_set(ast::MethodDec* def)
  {
    def_ = def;
  }

}

#endif // !TYPE_METHOD_HXX
