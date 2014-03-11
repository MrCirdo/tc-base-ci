EXTRA_DIST += type/README.txt type/tiger_type.i
noinst_LTLIBRARIES += type/libtype.la

type_libtype_la_SOURCES =						\
  type/fwd.hh type/types.hh						\
  type/array.hh type/array.cc type/array.hxx				\
  type/builtin-types.hh type/builtin-types.cc				\
  type/field.hh type/field.cc type/field.hxx				\
  type/function.hh type/function.cc type/function.hxx			\
  type/named.hh type/named.cc type/named.hxx				\
  type/record.hh type/record.cc type/record.hxx				\
  type/type.hh type/type.hxx type/type.cc				\
  type/type-checker.hh type/type-checker.hxx type/type-checker.cc	\
  type/libtype.hh type/libtype.cc

type_libtype_la_SOURCES +=					\
  type/attribute.hh type/attribute.cc type/attribute.hxx	\
  type/class.hh type/class.cc type/class.hxx			\
  type/method.hh type/method.cc type/method.hxx

TESTS += type/test-type
type_test_type_LDADD = $(libtype)

TASKS += type/tasks.hh type/tasks.cc
