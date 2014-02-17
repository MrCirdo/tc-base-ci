EXTRA_DIST += task/README.txt

# Libast
noinst_LTLIBRARIES += task/libtask.la
task_libtask_la_SOURCES =						\
  task/fwd.hh task/libtask.hh						\
  task/task.hh task/task.hxx task/task.cc				\
  task/boolean-task.hh task/boolean-task.cc				\
  task/function-task.hh task/function-task.cc				\
  task/int-task.hh task/int-task.cc					\
  task/string-task.hh task/string-task.cc				\
  task/multiple-string-task.hh task/multiple-string-task.cc		\
  task/disjunctive-task.hh task/disjunctive-task.cc			\
  task/task-register.hh task/task-register.cc task/task-register.hxx

# Be sure to fetch the argp we ship.
task_libtask_la_CPPFLAGS =			\
  $(AM_CPPFLAGS)				\
  -I$(top_srcdir)/lib/argp

TASKS += task/tasks.hh task/tasks.cc
