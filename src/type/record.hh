/**
 ** \file type/record.hh
 ** \brief The class Record.
 */
#ifndef TYPE_RECORD_HH
# define TYPE_RECORD_HH

# include <list>

# include <misc/indent.hh>
# include <misc/symbol.hh>
# include <type/type.hh>
# include <type/field.hh>
# include <type/fwd.hh>

namespace type
{
  /** \brief Record types.
   **
   ** List of Field s. */
  class Record : public Type
  {
    /** \name Field elementary manipulation.
     ** \{ */
  public:
    /// Return the type associated to \a key.
    const Type* field_type(const misc::symbol key) const;
    /** \brief Return the index of the field associated to \a key.
     **
     ** The index of a field is its position in the list. */
    int field_index(const misc::symbol key) const;
    /** \} */

    /** \name Internal Field list manipulators.
     ** \{ */
  public:
    /// List of Field's.
    typedef std::list<Field> fields_type;
    /// Return the Field list stored in this (read only).
    const fields_type& fields_get() const;

    /// Add an already existing Field to the list.
    void field_add(const Field& field);
    /// Create a Field then add it to the list.
    void field_add(const misc::symbol name, const Type& type);

    /// Iterators over Field's.
    typedef fields_type::const_iterator const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
    /** \} */

  // FIXME: Some code was deleted here (Inherited virtual methods).

  protected:
    /// Fields list.
    fields_type fields_;
  };


} // namespace type

# include <type/record.hxx>

#endif // !TYPE_RECORD_HH
