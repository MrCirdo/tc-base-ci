/**
 ** \file type/types.hh
 ** \brief Include all exported headers.
 */

#ifndef TYPE_TYPES_HH
# define TYPE_TYPES_HH

// FIXME: We should include "attribute.hh" and "class.hh" as well, but
// currently that would break the compilation (because of recursive
// dependencies).  Investigate and fix this.
# include <type/builtin-types.hh>
# include <type/function.hh>
# include <type/record.hh>
# include <type/array.hh>
# include <type/field.hh>
# include <type/named.hh>
# include <type/type.hh>

#endif // !TYPE_TYPES_HH
