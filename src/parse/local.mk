EXTRA_DIST += parse/tiger_parse.i

## -------------------- ##
## Scanner generation.  ##
## -------------------- ##

# A Flex wrapper for C++.
FLEXXX = $(top_builddir)/build-aux/bin/flex++
FLEXXX_IN = $(top_srcdir)/build-aux/bin/flex++.in
$(FLEXXX): $(FLEXXX_IN)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) build-aux/bin/flex++

MAINTAINERCLEANFILES += parse/scantiger.cc

EXTRA_DIST += parse/scantiger.ll
# The dependency is on flex++.in and not flex++, since flex++ is
# regenerated at distribution time, and voids the time stamps (which
# we don't want!).
parse/scantiger.cc: parse/scantiger.ll $(FLEXXX_IN)
	$(AM_V_GEN)mkdir -p $(@D)
	$(AM_V_at)rm -f $@
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) $(FLEXXX)
# Guarantees atomic generation of the output.
	$(AM_V_at)$(FLEXXX) $< $@ $(FLEXXXFLAGS)

## ------------------- ##
## Parser generation.  ##
## ------------------- ##

# A Bison wrapper for C++.
BISONXX = $(top_builddir)/build-aux/bin/bison++
BISONXX_IN = $(top_srcdir)/build-aux/bin/bison++.in
$(BISONXX): $(BISONXX_IN)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) build-aux/bin/bison++

BISONXXFLAGS =					\
  $(if $(V:0=),--verbose)
AM_BISONFLAGS =					\
  --report=all

# We do not use Automake features here.
SOURCES_PARSETIGER_YY_PARSER =			\
  parse/parsetiger.hh				\
  parse/parsetiger.cc
SOURCES_PARSETIGER_YY_OTHER =			\
  parse/position.hh				\
  parse/location.hh
SOURCES_PARSETIGER_YY =				\
  $(SOURCES_PARSETIGER_YY_PARSER)		\
  $(SOURCES_PARSETIGER_YY_OTHER)
BUILT_SOURCES += $(SOURCES_PARSETIGER_YY)

# Ship parse/stack.hh only if GLR is disabled, as Bison does not
# generate this file for GLR parsers.
dist-hook:
	@grep '^%glr-parser$$' $(srcdir)/parse/parsetiger.yy >/dev/null \
	  || cp -p $(srcdir)/parse/stack.hh $(distdir)/parse

# Compile the parser and save cycles.
# This code comes from "Handling Tools that Produce Many Outputs",
# from the Automake documentation.
EXTRA_DIST +=					\
  parse/parsetiger.stamp			\
  parse/parsetiger.yy
# The dependency is on bison++.in and not bison++, since bison++ is
# regenerated at distribution time, and voids the time stamps (which
# we don't want!).
parse/parsetiger.stamp: parse/parsetiger.yy $(BISONXX_IN)
	$(AM_V_GEN)mkdir -p $(@D)
	$(AM_V_at)rm -f $@ $@.tmp
	$(AM_V_at)echo '$@ rebuilt because of: $?' >$@.tmp
	$(AM_V_at)$(MAKE) $(BISONXX)
	$(AM_V_at)$(BISONXX) $(BISONXXFLAGS) --	\
	  $< $(srcdir)/parse/parsetiger.cc	\
	  $(AM_BISONFLAGS) $(BISONFLAGS)
	$(AM_V_at)mv -f $@.tmp $@

## If Make does not know it will generate in the srcdir, then when
## trying to compile from *.cc to *.lo, it will not apply VPATH
## lookup, since it expects the file to be in builddir.  So *here*,
## make srcdir explicit.
$(addprefix $(srcdir)/, $(SOURCES_PARSETIGER_YY)): parse/parsetiger.stamp
	$(AM_V_GEN)if test -f $@; then :; else	\
	  rm -f $<;				\
	  $(MAKE) $(AM_MAKEFLAGS) $<;		\
	fi

# We tried several times to run make from ast/ to build position.hh and
# location.hh.  Unfortunately, because of different, but equivalent,
# paths, BSD Make was unable to build them.  The following hook is
# here to address this.
.PHONY: generate-parser
generate-parser: $(SOURCES_PARSETIGER_YY)

CLEANFILES += parse/prelude.cc
parse/prelude.cc: $(top_srcdir)/data/prelude.tih
	$(AM_V_GEN)$(AWK)						\
	   'BEGIN {							\
	     print("#include \"parse/tiger-parser.hh\"");		\
	     print("");							\
	     print("namespace parse");					\
	     print("{");						\
	     print("  const char* TigerParser::prelude () const");	\
	     print("  {");						\
	     print("    return");					\
	   }								\
	   /^\#(<<|>>)/ {						\
	     next;							\
	   }								\
	   {								\
	     gsub(/[\\\"]/, "\\\\&", $$0);				\
	     print("      \"" $$0 "\\n\"");				\
	   }								\
	   END {							\
	     print("    ;");						\
	     print("  }");						\
	     print("} // namespace parse");				\
	   }'								\
	  $(top_srcdir)/data/prelude.tih >$@.tmp
	$(AM_V_at)mv $@.tmp $@


## ---------- ##
## libparse.  ##
## ---------- ##

noinst_LTLIBRARIES += parse/libparse.la

parse_libparse_la_SOURCES =				\
  parse/fwd.hh						\
  $(SOURCES_PARSETIGER_YY_OTHER)			\
  parse/metavar-map.hh parse/metavar-map.hxx		\
  parse/tweast.hh parse/tweast.cc parse/tweast.hxx

# Use a convenience library to compile all source including
# parse/parsetiger.hh with additional flags so as to avoid warnings
# about broken strict aliasing rules (see Automake's manual, section
# ``Per-Object Flags Emulation'').
parse_libparse_la_LIBADD = parse/libparsetiger.la
noinst_LTLIBRARIES += parse/libparsetiger.la
parse_libparsetiger_la_SOURCES =		\
  $(SOURCES_PARSETIGER_YY_PARSER)		\
  parse/tiger-parser.hh parse/tiger-parser.cc	\
  parse/scantiger.hh parse/scantiger.cc		\
  parse/libparse.hh parse/libparse.cc
parse_libparsetiger_la_CXXFLAGS = $(AM_CXXFLAGS) $(NO_STRICT_ALIASING_CXXFLAGS)

nodist_parse_libparsetiger_la_SOURCES =		\
  parse/prelude.cc

## ------- ##
## Tests.  ##
## ------- ##

TESTS +=					\
  parse/test-parse				\
  parse/test-tweast

# Find the prelude.
parse_test_parse_CPPFLAGS = $(AM_CPPFLAGS) -DPKGDATADIR=\"$(pkgdatadir)\"

parse_test_parse_LDADD = $(libparse)

parse_test_tweast_LDADD = $(libparse)


TASKS += parse/tasks.hh parse/tasks.cc
