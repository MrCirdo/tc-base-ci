noinst_LTLIBRARIES += regalloc/libregalloc.la
regalloc_libregalloc_la_SOURCES =					\
   regalloc/color.hh regalloc/color.cc					\
   regalloc/regallocator.hh regalloc/regallocator.cc			\
   regalloc/libregalloc.cc regalloc/libregalloc.hh

TESTS += regalloc/test-regalloc
regalloc_test_regalloc_LDADD = $(libregalloc) $(libtarget)

EXTRA_DIST += regalloc/tiger_regalloc.i

TASKS += regalloc/tasks.hh regalloc/tasks.cc
