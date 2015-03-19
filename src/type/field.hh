/**
 ** \file type/field.hh
 ** \brief The class Field (of a record type).
 */
#ifndef TYPE_FIELD_HH
# define TYPE_FIELD_HH

# include <misc/symbol.hh>
# include <type/type.hh>
# include <type/fwd.hh>

namespace type
{

  /** \brief The base type for Record fields.
   **
   ** Very much like Named, but it is *not* a Type. */
  class Field
  {
    /** \name Destructors
     ** \{ */
  public:
    virtual ~Field();
    /** \} */

    /** \name Ctor & dtor.
     ** \{ */
  public:
    /** \brief Construct a Field.
     ** \param name field's identifier.
     ** \param type field's type. */
    Field(misc::symbol name, const Type& type);
    /** \} */

    /** \name Accessors.
     ** \{ */
  public:
    /// Return the field's name.
    misc::symbol name_get() const;
    /// Return the field's type.
    const Type& type_get() const;
    /** \} */

  public:
    /// Print the field.
    virtual std::ostream& dump(std::ostream& ostr) const;

  protected:
    /// Field's identifier.
    misc::symbol name_;

    /// Field's type.
    const Type& type_;
  };

  /// Overload redirection operator for Field.
  std::ostream& operator<<(std::ostream& ostr, const Field& obj);


} // namespace type

# include <type/field.hxx>

#endif // !TYPE_FIELD_HH
