include $(top_srcdir)/src/tc.mk
AUTOMAKE_OPTIONS = subdir-objects

# We work on C++ only.  This way we don't have to list the sources of
# programs foo whose sources are exactly foo.cc.  A common pattern for
# tests.
AM_DEFAULT_SOURCE_EXT = .cc

BUILT_SOURCES =
CLEANFILES = $(EXTRA_PROGRAMS)
EXTRA_DIST =
MAINTAINERCLEANFILES =
TESTS =
EXTRA_PROGRAMS = $(TESTS)
dist_noinst_DATA =
noinst_LTLIBRARIES =

# Our tests should be run only if the sources are updated: they are
# self contained, and two runs in a row cannot differ.
RECHECK_LOGS =

# Find configuration headers.
AM_CPPFLAGS += -I $(top_builddir)

## ------- ##
## Tasks.  ##
## ------- ##

TASKS =
include task/local.mk
include ast/local.mk
include parse/local.mk
include object/local.mk

EXTRA_DIST += tiger_common.i

## ------------ ##
## version.cc.  ##
## ------------ ##

EXTRA_DIST += version.cc.in
CLEANFILES += version.stamp
version.stamp: $(top_srcdir)/ChangeLog $(srcdir)/version.cc.in
	$(AM_V_GEN)rm -f version.tmp
	$(AM_V_at)touch version.tmp
# Be sure not to have `/' in Id.  The embedded date may be
# separated by `/' instead of `-', what sed dislikes.
	$(AM_V_at)\
	Id=`sed -n '/^\$$Id/{s,/,-,g;p;q;}' $(top_srcdir)/ChangeLog`; \
	sed -e "s/@ID@/$$Id/" $(srcdir)/version.cc.in >version.cc.tmp
	$(AM_V_at)$(top_srcdir)/build-aux/bin/move-if-change \
	  version.cc.tmp version.cc
	$(AM_V_at)mv -f version.tmp version.stamp

version.cc: version.stamp
	$(AM_V_at)if test -f version.cc; then :; else \
	  rm -f version.stamp; \
	  $(MAKE) $(AM_MAKEFLAGS) version.stamp; \
	fi


## ------- ##
## libtc.  ##
## ------- ##

# If this library were a convenience library (noinst_), linking is
# considerably slown down (at least on Darwin).  For tcsh this is
# very penalizing.
lib_LTLIBRARIES = libtc.la
libtc_la_SOURCES = version.hh
nodist_libtc_la_SOURCES = version.cc
BUILT_SOURCES += $(nodist_libtc_la_SOURCES)
CLEANFILES += $(nodist_libtc_la_SOURCES)

## Don't forget that if liba depends on libb, then libb must be
## specified *after* liba.
##
## We cannot use $(libfoo) because some libraries appear several
## times, resulting in a library comprising several definitions of
## some symbols.
libtc_la_LIBADD =				\
	$(libobject_la)				\
	$(libparse_la)				\
	$(libast_la)				\
	$(libmisc_la)				\
	$(libargp_la)


## ---- ##
## tc.  ##
## ---- ##

bin_PROGRAMS = tc
dist_tc_SOURCES =				\
  doc.hh					\
  $(TASKS)					\
  common.cc common.hh				\
  tc.cc
# libtask is added to tc directly, and not to libtc (see below).  If
# it were added to libtc, it would create a least one undefined symbol
# (`U' in nm) in it: the global variable `error'.  Some linkers can
# perfectly deal with this and link libtc without the missing (but
# unused) symbol, e.g. in tcsh (GNU ld on Linux for instance); but
# some linkers report an error and refuse to link libtc (Apple's ld on
# Darwin, to mention it).
tc_LDADD = $(libtask_la) libtc.la

