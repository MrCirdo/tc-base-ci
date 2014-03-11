EXTRA_DIST += object/tiger_object.i

noinst_LTLIBRARIES += object/libobject.la

object_libobject_la_SOURCES = object/libobject.hh object/libobject.cc

object_libobject_la_SOURCES += object/binder.hh object/binder.cc

object_libobject_la_SOURCES += object/type-checker.hh object/type-checker.cc

object_libobject_la_SOURCES +=				\
  object/renamer.hh object/renamer.cc			\
  object/desugar-visitor.hh object/desugar-visitor.cc


# Tests.
TESTS += object/test-parse
object_test_parse_LDADD = $(libparse) $(libobject)

TESTS += object/test-bind
object_test_bind_LDADD = $(libparse) $(libobject)

TESTS += object/test-type
object_test_type_LDADD = $(libparse) $(libobject)

# FIXME: Add a test for object::Renamer.

TESTS += object/test-desugar
object_test_desugar_LDADD = $(libparse) $(libobject)


TASKS += object/tasks.hh object/tasks.cc
