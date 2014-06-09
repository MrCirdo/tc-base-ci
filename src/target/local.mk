# A MonoBURG wrapper.
MONOBURGXX = $(top_builddir)/build-aux/bin/monoburg++
MONOBURGXX_IN = $(top_srcdir)/build-aux/bin/monoburg++.in
$(MONOBURGXX): $(MONOBURGXX_IN)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) build-aux/bin/monoburg++

include target/mips/local.mk
include target/ia32/local.mk

# Libtarget
noinst_LTLIBRARIES += target/libtarget.la
target_libtarget_la_SOURCES =					\
  target/fwd.hh							\
  target/cpu.hh target/cpu.cc					\
  target/cpu-limits.hh						\
  target/assembly.hh target/assembly.cc				\
  target/codegen.hh target/codegen.hxx target/codegen.cc	\
  target/target.hh target/target.cc				\
  target/libtarget.hh target/libtarget.cc
target_libtarget_la_LIBADD =			\
  target/ia32/libtarget_ia32.la			\
  target/mips/libtarget_mips.la

# The original Tiger runtime in C.
dist_noinst_DATA += target/tiger-runtime.c

EXTRA_DIST += target/tiger_target.i

TASKS += target/tasks.hh target/tasks.cc
