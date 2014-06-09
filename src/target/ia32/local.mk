dist_noinst_DATA +=				\
  target/ia32/runtime-gnu-linux.s		\
  target/ia32/runtime-freebsd.s

CLEANFILES += target/ia32/runtime-gnu-linux.cc
target/ia32/runtime-gnu-linux.cc: target/ia32/runtime-gnu-linux.s
	$(AM_V_GEN)$(AWK)						\
	   'BEGIN {							\
	     print("#include \"target/ia32/gas-assembly.hh\"");		\
	     print("");							\
	     print("namespace target {");				\
	     print("namespace ia32 {");					\
	     print("const char* GasAssembly::runtime(bool gc) const");	\
	     print("{");						\
	     print("  if (!gc)");					\
	     print("    return \"\\");					\
	   }								\
	   /^\#(<<|>>)/ {						\
	     next;							\
	   }								\
	   {								\
	     gsub(/[\\\"]/, "\\\\&", $$0);				\
	     print($$0 "\\n\\");					\
	   }								\
	END { 								\
	  print("\";");							\
	}'								\
	  $< >$@.tmp
	$(AM_V_at)$(AWK)						\
	   'BEGIN {							\
	     print("  else");						\
	     print("    return \"\\");					\
	   }								\
	   /^\#(<<|>>)/ {						\
	     next;							\
	   }								\
	   {								\
	     gsub(/[\\\"]/, "\\\\&", $$0);				\
	     gsub(/call[ \t]+malloc/, "call\tGC_malloc", $$0);		\
	     print($$0 "\\n\\");					\
	   }								\
	END { 								\
	  print("\";");							\
	  print("}");							\
	  print("} // namespace ia32");					\
	  print("} // namespace target");				\
	  print("");							\
	}'								\
	  $< >>$@.tmp
	$(AM_V_at)mv $@.tmp $@

# FIXME: According to Automake's manual, `target/ia32/codegen.cc' is superfluous
# here, as it is a known dependency of target/ia32/libtarget_ia32.la.
BUILT_SOURCES += target/ia32/codegen.hh target/ia32/codegen.cc

EXTRA_DIST +=					\
  $(IA32_CODEGEN_GRAMMAR)			\
  target/ia32/prologue.hh			\
  target/ia32/epilogue.cc
IA32_CODEGEN_GRAMMAR =				\
  target/ia32/binop.brg				\
  target/ia32/call.brg				\
  target/ia32/cjump.brg				\
  target/ia32/exp.brg				\
  target/ia32/mem.brg				\
  target/ia32/move.brg				\
  target/ia32/move_store.brg			\
  target/ia32/move_load.brg			\
  target/ia32/stm.brg				\
  target/ia32/temp.brg				\
  target/ia32/tree.brg

EXTRA_DIST += $(srcdir)/target/ia32/codegen.stamp
# The dependency is on monoburg++.in and not monoburg++, since
# monoburg++ is regenerated at distribution time, and voids the time
# stamps (which we don't want!).
$(srcdir)/target/ia32/codegen.stamp: $(IA32_CODEGEN_GRAMMAR) $(srcdir)/target/ia32/prologue.hh $(srcdir)/target/ia32/epilogue.cc $(MONOBURGXX_IN)
	$(AM_V_GEN)$(MAKE) $(AM_MAKEFLAGS) $(MONOBURGXX)
	$(AM_V_at)rm -f $@ $@.tmp $(srcdir)/target/ia32/codegen.hh \
	  $(srcdir)/target/ia32/codegen.cc
	$(AM_V_at)touch $@.tmp
	$(AM_V_at)$(MONOBURGXX) $(srcdir)/target/ia32/tree.brg    \
	  $(srcdir)/target/ia32/codegen.cc target/ia32/codegen.hh \
	  -n TARGET_IA32_CODEGEN --quiet
	$(AM_V_at)chmod a-w $(srcdir)/target/ia32/codegen.hh \
	  $(srcdir)/target/ia32/codegen.cc
	$(AM_V_at)mv -f $@.tmp $@
$(srcdir)/target/ia32/codegen.hh $(srcdir)/target/ia32/codegen.cc: $(srcdir)/target/ia32/codegen.stamp
	$(AM_V_GEN)if test -f $@; then				\
	  touch $@;						\
	else							\
	  rm -f $(srcdir)/target/ia32/codegen.stamp;		\
	  $(MAKE) $(AM_MAKEFLAGS) target/ia32/codegen.stamp;	\
	fi

noinst_LTLIBRARIES += target/ia32/libtarget_ia32.la

target_ia32_libtarget_ia32_la_SOURCES =				\
  target/ia32/fwd.hh						\
  target/ia32/cpu.hh target/ia32/cpu.cc				\
  target/ia32/gas-layout.hh target/ia32/gas-layout.cc		\
  target/ia32/gas-assembly.hh target/ia32/gas-assembly.cc	\
  target/ia32/codegen.cc target/ia32/codegen.hh			\
  target/ia32/target.hh target/ia32/target.cc

nodist_target_ia32_libtarget_ia32_la_SOURCES =			\
  target/ia32/runtime-gnu-linux.cc

TESTS += target/ia32/test-target
target_ia32_test_target_LDADD = $(libtranslate) $(libtarget)
