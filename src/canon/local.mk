noinst_LTLIBRARIES += canon/libcanon.la
canon_libcanon_la_SOURCES =						\
  canon/canon.hh canon/canon.cc						\
  canon/basic-block.hh canon/basic-block.hxx canon/basic-block.cc	\
  canon/traces.hh canon/traces.cc					\
  canon/libcanon.cc canon/libcanon.hh

EXTRA_DIST += canon/tiger_canon.i

## FIXME: Does not seem to be working.
## TESTS += canon/test-canon
## canon_test_canon_LDADD = $(libcanon)
## TESTS = canon/test-canon

TASKS += canon/tasks.hh canon/tasks.cc
