## --------- ##
## libmisc.  ##
## --------- ##
AM_DEFAULT_SOURCE_EXT = .cc
EXTRA_DIST = misc/tiger_misc.i

AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_builddir)/lib $(BOOST_CPPFLAGS)

noinst_LTLIBRARIES = misc/libmisc.la
misc_libmisc_la_SOURCES =						\
  misc/fwd.hh								\
  misc/libmisc.hh							\
  misc/algorithm.hh misc/algorithm.hxx					\
  misc/contract.hh misc/contract.cc					\
  misc/deref.hh misc/deref.hxx misc/deref.cc				\
  misc/error.hh misc/error.hxx misc/error.cc				\
  misc/escape.hh misc/escape.hxx misc/escape.cc				\
  misc/file-library.hh misc/file-library.hxx misc/file-library.cc	\
  misc/flex-lexer.hh							\
  misc/generic-variant.hh misc/generic-variant.hxx			\
  misc/graph.hh misc/graph.hxx						\
  misc/indent.hh misc/indent.cc						\
  misc/list.hh misc/list.hxx						\
  misc/map.hh misc/map.hxx						\
  misc/endomap.hh misc/endomap.hxx					\
  misc/pair.hh misc/pair.hxx						\
  misc/path.hh misc/path.hxx misc/path.cc				\
  misc/ref.hh misc/ref.hxx						\
  misc/scoped-map.hh misc/scoped-map.hxx				\
  misc/select-const.hh							\
  misc/set.hh misc/set.hxx						\
  misc/separator.hh misc/separator.hxx					\
  misc/symbol.hh misc/symbol.hxx misc/symbol.cc				\
  misc/timer.hh misc/timer.hxx misc/timer.cc				\
  misc/unique.hh misc/unique.hxx					\
  misc/variant.hh misc/variant.hxx					\
  misc/xalloc.hh misc/xalloc.hxx misc/xalloc.cc


## ------- ##
## Tests.  ##
## ------- ##

TESTS =						\
  misc/test-deref				\
  misc/test-error				\
  misc/test-escape				\
  misc/test-generic-variant			\
  misc/test-graph				\
  misc/test-indent				\
  misc/test-path				\
  misc/test-separator				\
  misc/test-scoped				\
  misc/test-symbol				\
  misc/test-timer				\
  misc/test-unique				\
  misc/test-variant				\
  misc/test-xalloc
EXTRA_PROGRAMS = $(TESTS)
CLEANFILES = $(TESTS)
RECHECK_LOGS =
misc_test_generic_variant_CXXFLAGS  = -Wno-unused
misc_test_variant_CXXFLAGS          = -Wno-unused

LDADD = misc/libmisc.la
