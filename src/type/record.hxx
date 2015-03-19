/**
 ** \file type/record.hxx
 ** \brief Inline methods for type::Record.
 */
#ifndef TYPE_RECORD_HXX
# define TYPE_RECORD_HXX

# include <type/record.hh>
# include <misc/contract.hh>

namespace type
{
  inline const Record::fields_type&
  Record::fields_get() const
  {
    return fields_;
  }

  inline void
  Record::field_add(const Field& field)
  {
    fields_.push_back(field);
  }

  inline void
  Record::field_add(const misc::symbol name, const Type& type)
  {
    fields_.emplace_back(name, type);
  }

  inline Record::const_iterator
  Record::begin() const
  {
    return fields_.begin();
  }

  inline Record::const_iterator
  Record::end() const
  {
    return fields_.end();
  }
} // namespace type

#endif // !TYPE_RECORD_HXX
