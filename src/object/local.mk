EXTRA_DIST += object/tiger_object.i

noinst_LTLIBRARIES += object/libobject.la

object_libobject_la_SOURCES = object/libobject.hh object/libobject.cc





# Tests.





TASKS += object/tasks.hh object/tasks.cc
