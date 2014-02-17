TS_SH = testsuite/ex1-test testsuite/permute-test
TS_PROGS =

TESTS = $(TS_PROGS) $(TS_SH)

AM_CPPFLAGS = -I$(top_srcdir)
check_PROGRAMS = $(TS_PROGS) testsuite/ex1 testsuite/ex3 testsuite/ex4

LDADD = libargp.la

EXTRA_DIST += $(TS_SH) testsuite/run-tests
CLEANFILES = testsuite/test.out
TEST_ENVIRONMENT = \
  srcdir="$(srcdir)/testsuite" $(top_srcdir)/testsuite/run-tests
