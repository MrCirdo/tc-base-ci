## Process this file with automake --
noinst_LTLIBRARIES += desugar/libdesugar.la
desugar_libdesugar_la_SOURCES =						\
	desugar/desugar-visitor.hh desugar/desugar-visitor.cc			\
	desugar/bound-checking-visitor.hh desugar/bound-checking-visitor.cc	\
	desugar/libdesugar.hh desugar/libdesugar.cc

TESTS +=				\
  desugar/test-string-cmp-desugar			\
  desugar/test-for-loops-desugar			\
  desugar/test-bound-checking

desugar_test_string_cmp_desugar_LDADD = $(libdesugar)
desugar_test_string_cmp_desugar_CPPFLAGS = \
  $(AM_CPPFLAGS) -DPKGDATADIR=\"$(pkgdatadir)\"

desugar_test_for_loops_desugar_LDADD = $(libdesugar)
desugar_test_for_loops_desugar_CPPFLAGS = $(AM_CPPFLAGS) -DPKGDATADIR=\"$(pkgdatadir)\"

desugar_test_bound_checking_LDADD = $(libdesugar)
desugar_test_bound_checking_CPPFLAGS = $(AM_CPPFLAGS) -DPKGDATADIR=\"$(pkgdatadir)\"


TASKS += desugar/tasks.hh desugar/tasks.cc
