dist_noinst_DATA += target/mips/runtime.s

CLEANFILES += target/mips/runtime.cc
target/mips/runtime.cc: $(srcdir)/target/mips/runtime.s
	$(AM_V_GEN)$(AWK)						\
	   'BEGIN {							\
	     print("#include \"target/mips/spim-assembly.hh\"");	\
	     print("");							\
	     print("namespace target {");				\
	     print("namespace mips {");					\
	     print("const char* SpimAssembly::runtime(bool) const");	\
	     print("{");						\
	     print("  return \"\\");					\
	   }								\
	   /^\#(<<|>>)/ {						\
	     next;							\
	   }								\
	   {								\
	     gsub(/[\\\"]/, "\\\\&", $$0);				\
	     print($$0 "\\n\\");}					\
	   END {							\
	     print("\";");						\
	     print("}");						\
	     print("} // namespace mips");				\
	     print("} // namespace target");				\
	     print("");							\
	   }'								\
	  $< >$@.tmp
	$(AM_V_at)mv $@.tmp $@

BUILT_SOURCES += target/mips/codegen.hh target/mips/codegen.cc

EXTRA_DIST +=					\
  $(MIPS_CODEGEN_GRAMMAR)			\
  target/mips/prologue.hh			\
  target/mips/epilogue.cc
MIPS_CODEGEN_GRAMMAR =				\
  target/mips/binop.brg				\
  target/mips/call.brg				\
  target/mips/cjump.brg				\
  target/mips/exp.brg				\
  target/mips/mem.brg				\
  target/mips/move.brg				\
  target/mips/move_store.brg			\
  target/mips/move_load.brg			\
  target/mips/stm.brg				\
  target/mips/temp.brg				\
  target/mips/tree.brg

EXTRA_DIST += $(srcdir)/target/mips/codegen.stamp
# The dependency is on monoburg++.in and not monoburg++, since
# monoburg++ is regenerated at distribution time, and voids the time
# stamps (which we don't want!).
$(srcdir)/target/mips/codegen.stamp: $(MIPS_CODEGEN_GRAMMAR) $(srcdir)/target/mips/prologue.hh $(srcdir)/target/mips/epilogue.cc $(MONOBURGXX_IN)
	$(AM_V_GEN)$(MAKE) $(AM_MAKEFLAGS) $(MONOBURGXX)
	$(AM_V_at)rm -f $@ $@.tmp $(srcdir)/target/mips/codegen.hh \
	  $(srcdir)/target/mips/codegen.cc
	$(AM_V_at)touch $@.tmp
	$(AM_V_at)$(MONOBURGXX) $(srcdir)/target/mips/tree.brg    \
	  $(srcdir)/target/mips/codegen.cc target/mips/codegen.hh \
	  -n TARGET_MIPS_CODEGEN --quiet
	$(AM_V_at)chmod a-w $(srcdir)/target/mips/codegen.hh \
	  $(srcdir)/target/mips/codegen.cc
	$(AM_V_at)mv -f $@.tmp $@
$(srcdir)/target/mips/codegen.hh $(srcdir)/target/mips/codegen.cc: $(srcdir)/target/mips/codegen.stamp
	$(AM_V_GEN)if test -f $@; then				\
	  touch $@;						\
	else							\
	  rm -f $(srcdir)/target/mips/codegen.stamp;		\
	  $(MAKE) $(AM_MAKEFLAGS) target/mips/codegen.stamp;	\
	fi

noinst_LTLIBRARIES += target/mips/libtarget_mips.la
target_mips_libtarget_mips_la_SOURCES =				\
  target/mips/cpu.hh target/mips/cpu.cc				\
  target/mips/spim-layout.hh target/mips/spim-layout.cc		\
  target/mips/spim-assembly.hh target/mips/spim-assembly.cc	\
  target/mips/codegen.hh target/mips/codegen.cc			\
  target/mips/target.hh target/mips/target.cc

nodist_target_mips_libtarget_mips_la_SOURCES = target/mips/runtime.cc

TESTS += target/mips/test-target
target_mips_test_target_LDADD = $(libtranslate) $(libtarget)
