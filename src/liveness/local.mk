CLEANFILES += *~ *.gv

noinst_LTLIBRARIES += liveness/libliveness.la
liveness_libliveness_la_SOURCES =						\
   liveness/flowgraph.hh liveness/flowgraph.hxx						\
   liveness/liveness.hh liveness/liveness.cc						\
   liveness/interference-graph.hh liveness/interference-graph.cc liveness/interference-graph.hxx	\
   liveness/libliveness.hh liveness/libliveness.cc
liveness_libliveness_la_LDFLAGS = $(BOOST_GRAPH_LDFLAGS)
liveness_libliveness_la_LIBADD = $(BOOST_GRAPH_LIBS)

TESTS += liveness/test-flowgraph
liveness_test_flowgraph_LDADD = $(libliveness)

EXTRA_DIST += liveness/tiger_liveness.i

TASKS += liveness/tasks.hh liveness/tasks.cc
