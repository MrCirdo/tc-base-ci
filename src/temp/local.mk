noinst_LTLIBRARIES += temp/libtemp.la

temp_libtemp_la_SOURCES =				\
  temp/fwd.hh					\
  temp/identifier.hh temp/identifier.hxx		\
  temp/temp.hh temp/temp.cc				\
  temp/temp-set.hh temp/temp-set.cc			\
  temp/label.hh temp/label.cc				\
  temp/libtemp.hh temp/libtemp.cc

TESTS += temp/test-temp
temp_test_temp_LDADD = $(libtemp)

EXTRA_DIST += temp/tiger_temp.i

TASKS += temp/tasks.hh temp/tasks.cc
