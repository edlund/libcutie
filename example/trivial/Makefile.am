
AM_CFLAGS = \
	-std=c99 \
	-Wall \
	-Werror \
	-Wextra \
	-pedantic \
	-D_GNU_SOURCE \
	-I$(top_srcdir)/include

noinst_PROGRAMS = example

example_SOURCES = \
	example.c \
	robot.c \
	replicator.c
example_LDADD = \
	$(top_builddir)/source/libcutie.la

