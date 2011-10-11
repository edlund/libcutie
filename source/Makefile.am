
AM_CFLAGS = \
	-std=c99 \
	-Wall \
	-Wextra \
	-Wundef \
	-Werror \
	-pedantic \
	-I$(top_srcdir)/include \
	@GCOV_CFLAGS@

lib_LTLIBRARIES = \
	libcutie.la

libcutie_la_SOURCES = \
	class.c \
	panic.c
libcutie_la_LIBADD = @LIBOBJS@

CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov

