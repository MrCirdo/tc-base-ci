noinst_LTLIBRARIES += assem/libassem.la

assem_libassem_la_SOURCES =					\
  assem/fwd.hh assem/libassem.hh				\
  assem/instr.hh assem/instr.hxx assem/instr.cc			\
  assem/instrs.hh assem/instrs.cc				\
  assem/label.hh assem/label.hxx				\
  assem/move.hh assem/move.hxx					\
  assem/oper.hh assem/oper.hxx					\
  assem/comment.hh assem/comment.hxx				\
  assem/fragment.hh assem/fragment.hxx assem/fragment.cc	\
  assem/fragments.hh assem/fragments.cc				\
  assem/visitor.hh assem/visitor.hxx				\
  assem/layout.hh assem/layout.hxx assem/layout.cc

