noinst_LTLIBRARIES += translate/libtranslate.la

translate_libtranslate_la_SOURCES =				\
  translate/fwd.hh						\
  translate/access.hh translate/access.hxx translate/access.cc	\
  translate/exp.hh translate/exp.hxx translate/exp.cc		\
  translate/translation.hh translate/translation.cc		\
  translate/level.hh translate/level.hxx translate/level.cc	\
  translate/translator.hh translate/translator.cc		\
  translate/libtranslate.cc translate/libtranslate.hh

EXTRA_DIST += translate/tiger_translate.i

TASKS += translate/tasks.hh translate/tasks.cc
