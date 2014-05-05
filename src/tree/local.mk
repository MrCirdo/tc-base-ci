EXTRA_DIST += tree/README.txt tree/tiger_tree.i
noinst_LTLIBRARIES += tree/libtree.la

tree_libtree_la_SOURCES =				\
  tree/all.hh						\
  tree/fwd.hh						\
  tree/libtree.hh tree/libtree.cc			\
  tree/trees.hh tree/trees.cc				\
  tree/tree.hh tree/tree.hxx tree/tree.cc		\
  tree/exp.hh tree/exp.cc				\
  tree/stm.hh tree/stm.cc				\
  tree/cjump.hh tree/cjump.hxx tree/cjump.cc		\
  tree/label.hh tree/label.hxx tree/label.cc		\
  tree/name.hh tree/name.hxx tree/name.cc		\
  tree/binop.hh tree/binop.hxx tree/binop.cc		\
  tree/const.hh tree/const.hxx tree/const.cc		\
  tree/iterator.hh tree/iterator.hxx			\
  tree/mem.hh tree/mem.hxx tree/mem.cc			\
  tree/sxp.hh tree/sxp.hxx tree/sxp.cc			\
  tree/call.hh tree/call.cc				\
  tree/eseq.hh tree/eseq.hxx tree/eseq.cc		\
  tree/jump.hh tree/jump.hxx tree/jump.cc		\
  tree/move.hh tree/move.hxx tree/move.cc		\
  tree/seq.hh tree/seq.hxx tree/seq.cc			\
  tree/temp.hh tree/temp.hxx tree/temp.cc		\
  tree/fragment.hh tree/fragment.hxx tree/fragment.cc	\
  tree/fragments.hh tree/fragments.cc			\
  tree/visitor.hh tree/visitor.hxx
