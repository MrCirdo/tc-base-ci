## Process this file with automake --
noinst_LTLIBRARIES += inlining/libinlining.la
inlining_libinlining_la_SOURCES =			\
	inlining/inliner.hh inlining/inliner.cc			\
	inlining/pruner.hh inlining/pruner.cc			\
	inlining/libinlining.hh inlining/libinlining.cc
inlining_libinlining_la_LDFLAGS = $(BOOST_GRAPH_LDFLAGS)
inlining_libinlining_la_LIBADD = $(BOOST_GRAPH_LIBS)

TASKS += inlining/tasks.hh inlining/tasks.cc
