EXTRA_DIST += bind/tiger_bind.i

## --------- ##
## Libbind.  ##
## --------- ##

noinst_LTLIBRARIES += bind/libbind.la
bind_libbind_la_SOURCES =				\
	bind/binder.hh bind/binder.hxx bind/binder.cc		\
	bind/renamer.hh bind/renamer.hxx bind/renamer.cc	\
	bind/libbind.hh bind/libbind.cc


## ------- ##
## Tests.  ##
## ------- ##

TESTS += bind/test-bind
bind_test_bind_LDADD = $(libbind)


TASKS += bind/tasks.hh bind/tasks.cc
