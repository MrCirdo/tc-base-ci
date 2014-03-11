/**
 ** \file type/function.hh
 ** \brief The class Function.
 */
#ifndef TYPE_FUNCTION_HH
# define TYPE_FUNCTION_HH

# include <type/type.hh>
# include <type/record.hh>
# include <type/fwd.hh>

namespace type
{

  /** \brief Function types.
   **
   ** Encapsulate the signature of a function, ie the type structures
   ** of both function's arguments and its result.  */
  class Function : public Type
  {
  public:
    /** \brief Construct a Function.
     **
     ** \param formals type structures of formal arguments.
     ** \param result type structure of what function returns. */
    Function(const Record* formals, const Type& result);

    /** \brief Destructor.
     **/
    virtual ~Function();

    /** \name Accessors.
     ** \{ */
  public:
    /// Return the type structures of the function's arguments.
    const Record& formals_get() const;
    /// Return the type structure of the function's result.
    const Type& result_get() const;
    /** \} */

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Function).

  public:
    /// Print function's result's and formals's types.
    virtual std::ostream& dump(std::ostream& ostr) const override;

  protected:
    /// Formals' types.
    const Record* formals_;

    /// Result's type.
    const Type& result_;
  };

} // namespace type

# include <type/function.hxx>

#endif // !TYPE_FUNCTION_HH
