EXTRA_DIST += callgraph/tiger_callgraph.i

# Compiling.
# Libcallgraph
noinst_LTLIBRARIES += callgraph/libcallgraph.la
callgraph_libcallgraph_la_SOURCES =			\
	callgraph/libcallgraph.hh callgraph/libcallgraph.cc
callgraph_libcallgraph_la_LDFLAGS = $(BOOST_GRAPH_LDFLAGS)
callgraph_libcallgraph_la_LIBADD = $(BOOST_GRAPH_LIBS)

# The callgraph.
callgraph_libcallgraph_la_SOURCES +=					\
	callgraph/fundec-graph.hh callgraph/fundec-graph.hxx			\
	callgraph/call-graph-visitor.hh callgraph/call-graph-visitor.cc

TASKS += callgraph/tasks.hh callgraph/tasks.cc
