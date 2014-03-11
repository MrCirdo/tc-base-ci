/**
 ** \file type/builtin-types.hh
 ** \brief The classes Nil, Void, Int, String.
 */
#ifndef TYPE_BUILTIN_TYPES_HH
# define TYPE_BUILTIN_TYPES_HH

# include <type/type.hh>
# include <type/fwd.hh>

namespace type
{

  /// The builtin type of `nil' only (singleton class).
  class Nil : public Type
  {
    // Make it non-copyable.
    Nil(const Nil&) = delete;
    Nil & operator= (const Nil&) = delete;

  public:
    /// Return the unique instance of Nil.
    static const Nil& instance();

  public:
    virtual bool compatible_with(const Type& other) const override;

  public:
    /// Print "nil".
    virtual std::ostream& dump(std::ostream& ostr) const override;

  private:
    /** \brief Construct a Nil object
     ** (use restricted to internal functions). */
    Nil() = default;
  };


  // FIXME: Some code was deleted here (Other types : String, Int, Void).

} // namespace type

#endif // !TYPE_BUILTIN_TYPES_HH
