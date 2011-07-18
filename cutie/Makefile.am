
AM_CFLAGS = \
	-std=c99 \
	-Wall \
	-Wextra \
	-Wno-missing-field-initializers \
	-Werror \
	-pedantic \
	@GCOV_CFLAGS@

lib_LTLIBRARIES = \
	libcutie.la

libcutie_la_SOURCES = \
	class.c \
	mem.c \
	panic.c
libcutie_la_LIBADD = @LIBOBJS@

CLEANFILES = \
	config.h.in~ \
	cutie.h.in~ \
	*.gcda \
	*.gcno \
	*.gcov

nobase_include_HEADERS = \
	cutie.h

