
AM_CFLAGS = \
	-std=c99 \
    -Wall \
    -Werror \
    -Wextra \
    -Wno-missing-field-initializers \
    -pedantic \
    -I$(top_srcdir)/cutie

noinst_PROGRAMS = example

example_SOURCES = \
	example.c \
	robot.c \
	replicator.c
example_LDADD = \
	$(top_builddir)/cutie/libcutie.la

