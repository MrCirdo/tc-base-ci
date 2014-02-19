ast_basedir = ast/
ast_srcdir = $(srcdir)/ast
# Don't use ast_srcdir in the include, otherwise Automake can't resolve it.
include $(srcdir)/ast/ast-nodes.mk

EXTRA_DIST += ast/tiger_ast.i


noinst_LTLIBRARIES += ast/libast.la
ast_libast_la_SOURCES =					\
  ast/location.hh					\
  ast/all.hh						\
  ast/any-decs.hh ast/any-decs.hxx			\
  ast/var-decs.hh					\
  ast/type-decs.hh					\
  ast/function-decs.hh					\
  ast/method-decs.hh					\
  ast/decs.hh ast/decs.hxx ast/decs.cc			\
  ast/fwd.hh						\
  ast/visitor.hh					\
  $(AST_NODES)						\
  ast/default-visitor.hh ast/default-visitor.hxx	\
  ast/non-object-visitor.hh ast/non-object-visitor.hxx	\
  ast/object-visitor.hh ast/object-visitor.hxx		\
  ast/pretty-printer.hh ast/pretty-printer.cc		\
  ast/visitor.hxx					\
  ast/libast.hh ast/libast.cc


dist_noinst_DATA += ast/README.txt

TESTS += ast/test-ast
ast_test_ast_LDADD = $(libast)

TASKS += ast/tasks.hh ast/tasks.cc
