
noinst_LTLIBRARIES += astclone/libastclone.la
astclone_libastclone_la_SOURCES =				\
  astclone/cloner.hh astclone/cloner.hxx astclone/cloner.cc	\
  astclone/libastclone.hh astclone/libastclone.hxx

TESTS += astclone/test-cloner
astclone_test_cloner_LDADD = $(libastclone) $(libparse) $(libmisc) $(libsymbol)
astclone_test_cloner_CPPFLAGS = $(AM_CPPFLAGS) -DPKGDATADIR=\"$(pkgdatadir)\"


TASKS += astclone/tasks.hh astclone/tasks.cc
