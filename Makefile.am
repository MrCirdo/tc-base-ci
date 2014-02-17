ACLOCAL_AMFLAGS = -I build-aux/m4

CLEANFILES =
EXTRA_DIST =
dist_noinst_DATA =

if ENABLE_TCSH
  MAYBE_TCSH = tcsh
endif

include build-aux/local.mk
include data/local.mk

SUBDIRS =					\
  lib						\
  src						\
  $(MAYBE_TCSH)					\
  tests doc

EXTRA_DIST += bootstrap AUTHORS.txt NEWS.txt THANKS.txt

## --------------------- ##
## Version and authors.  ##
## --------------------- ##

BUILT_SOURCES = authors.h
CLEANFILES += authors.h tc.log.bz2
# Improve --version.
AUTHORS_H_GEN = $(srcdir)/build-aux/bin/authors.h-gen
EXTRA_DIST += AUTHORS.txt $(AUTHORS_H_GEN)
authors.h: AUTHORS.txt $(AUTHORS_H_GEN)
	$(AM_V_GEN)$(AUTHORS_H_GEN) $< >$@.tmp
	$(AM_V_at)$(top_srcdir)/build-aux/bin/move-if-change $@.tmp $@


## ------------------------------ ##
## Generating the documentation.  ##
## ------------------------------ ##

.PHONY: doc html
doc html:
	cd doc && $(MAKE) $(AM_MAKEFLAGS) $@


