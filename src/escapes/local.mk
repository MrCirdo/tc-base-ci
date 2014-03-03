EXTRA_DIST += escapes/tiger_escapes.i

# Compiling.
# Libescapes
noinst_LTLIBRARIES += escapes/libescapes.la
escapes_libescapes_la_SOURCES =				\
	escapes/libescapes.hh escapes/libescapes.cc

# Computing the escapes.
escapes_libescapes_la_SOURCES +=					  \
	escapes/escapes-visitor.hh escapes/escapes-visitor.cc

TASKS += escapes/tasks.hh escapes/tasks.cc
