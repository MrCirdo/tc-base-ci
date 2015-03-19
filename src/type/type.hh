/**
 ** \file type/type.hh
 ** \brief The class Type.
 */
#ifndef TYPE_TYPE_HH
# define TYPE_TYPE_HH

# include <type/fwd.hh>
# include <misc/xalloc.hh>

namespace type
{
  /// Abstract a type.
  class Type
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Destroys a Type.
    virtual ~Type();
    /** \} */


    /** \name Accessors.
     ** \{ */
  public:
    /// Return the actual type held by THIS.
    virtual const Type& actual() const;
    /** \} */


  public:
    /** \brief Whether two types are "compatible".
     **
     ** I.e., whether "a = b", "a <> b", "a := b" are correctly typed
     ** with a of type \a this, and b of type \a other).
     **
     ** By default two types are compatible (in the sense of "=" and "<>",
     ** not wrt an order) only when they are equal.
     **
     ** In the case of assignment, "rec := nil" is valid, but "nil := rec"
     ** is not, which suggest that we should have a non commutative
     ** assignment specific compatibility check.  But since "nil := ..."
     ** is incorrect syntactically, that is not needed.
     */
    virtual bool compatible_with(const Type& other) const;

  public:
    /// Report this on \a ostr.
    virtual std::ostream& dump(std::ostream& ostr) const = 0;
  };

  /// Overload redirection operator for Type.
  std::ostream& operator<<(std::ostream& ostr, const Type& t);


  /** \brief Compare two Type s.
   **
   ** Return true iff \a a and \a b are equivalent Tiger Types.  E.g.,
   ** if \a a and \a b are different but point to the same type, then
   ** return true. */
  bool operator==(const Type& lhs, const Type& rhs);
  /// !(a == b).
  bool operator!=(const Type& lhs, const Type& rhs);

  /// Hide actual types?  (i.e., print only the surface type?)
  extern const misc::xalloc<bool> hide_actual_types;

} // namespace type

# include <type/type.hxx>

#endif // !TYPE_TYPE_HH
