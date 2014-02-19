EXTRA_DIST += object/tiger_object.i

noinst_LTLIBRARIES += object/libobject.la

object_libobject_la_SOURCES = object/libobject.hh object/libobject.cc





# Tests.
TESTS += object/test-parse
object_test_parse_LDADD = $(libparse) $(libobject)





TASKS += object/tasks.hh object/tasks.cc
