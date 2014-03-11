EXTRA_DIST += overload/tiger_overload.i
noinst_LTLIBRARIES += overload/liboverload.la

overload_liboverload_la_SOURCES =			\
	overload/over-table.hh overload/over-table.hxx		\
	overload/binder.hh overload/binder.cc			\
	overload/type-checker.hh overload/type-checker.cc		\
	overload/liboverload.hh overload/liboverload.cc

TASKS += overload/tasks.hh overload/tasks.cc
