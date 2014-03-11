# Most headers are to be shipped and to be found in src/, e.g.
# tasks/tasks.hh is shipped in $(top_srcdir)/src/task/tasks.hh.  Some
# are *built* in src, e.g., $(top_builddir)/src/modules.hh.
AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += $(BOOST_CPPFLAGS)
# Find the prelude.
AM_CPPFLAGS += -DPKGDATADIR="\"$(pkgdatadir)\""
AM_CXXFLAGS = $(WARNING_CXXFLAGS)

# All our libraries, in the order of dependency.
libregalloc_la  = regalloc/libregalloc.la
libliveness_la  = liveness/libliveness.la
libassem_la     = assem/libassem.la
libcanon_la     = canon/libcanon.la
libtranslate_la = translate/libtranslate.la
libframe_la     = frame/libframe.la
libtarget_la    = target/libtarget.la
libtree_la      = tree/libtree.la
libtemp_la      = temp/libtemp.la
libinlining_la  = inlining/libinlining.la
libdesugar_la   = desugar/libdesugar.la
libtransform_la = transform/libtransform.la
liboverload_la  = overload/liboverload.la
libobject_la    = object/libobject.la
libtype_la      = type/libtype.la
libcallgraph_la = callgraph/libcallgraph.la
libescapes_la   = escapes/libescapes.la
libbind_la      = bind/libbind.la
libastclone_la  = astclone/libastclone.la
libparse_la     = parse/libparse.la
libast_la       = ast/libast.la
libtask_la      = task/libtask.la
libmisc_la      = $(top_builddir)/lib/misc/libmisc.la
libargp_la      = $(top_builddir)/lib/argp/libargp.la

# All our libraries...
libregalloc  = $(libregalloc_la)
libliveness  = $(libliveness_la)
libassem     = $(libassem_la)
libcanon     = $(libcanon_la)
libtranslate = $(libtranslate_la)
libframe     = $(libframe_la)
libtarget    = $(libtarget_la)
libtree      = $(libtree_la)
libtemp      = $(libtemp_la)
libinlining  = $(libinlining_la)
libdesugar   = $(libdesugar_la)
libtransform = $(libtransform_la)
liboverload  = $(liboverload_la)
libobject    = $(libobject_la)
libtype      = $(libtype_la)
libcallgraph = $(libcallgraph_la)
libescapes   = $(libescapes_la)
libbind      = $(libbind_la)
libastclone  = $(libastclone_la)
libparse     = $(libparse_la)
libast       = $(libast_la)
libtask      = $(libtask_la)
libmisc      = $(libmisc_la)
libargp      = $(libargp_la)

# ... and their dependencies.
libregalloc  += $(libliveness)
libliveness  += $(libassem)
libassem     += $(libtranslate)
libtranslate += $(libframe)
libframe     += $(libtree)
libtarget    += $(libtemp) $(libassem)
libtree      += $(libtemp)
libtemp      += $(libmisc)
libinlining  += $(libparse) $(libastclone) $(libdesugar) $(libcallgraph)
libdesugar   += $(libparse) $(libastclone) $(libbind) $(libtype)
libtransform += $(libastclone)
libtype      += $(libmisc)
libcallgraph += $(libmisc)
libbind      += $(libparse) $(libast)
libastclone  += $(libast)
libparse     += $(libmisc)
libobject    += $(libbind)
libobject    += $(libdesugar)
# libast already declares libmisc as dependency, but we have to add
# it manually to LDADD when libast is absent (i.e., at TC-1).
libparse     += $(libast)
libast       += $(libtype) $(libmisc)
