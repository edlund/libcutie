
AM_CFLAGS = \
	-std=c99 \
	-Wall \
	-Wextra \
	-Wno-missing-field-initializers \
	-Werror \
	-pedantic \
	@GCOV_CFLAGS@

lib_LTLIBRARIES = \
	libcutie.la \
	libcutie.std.la

libcutie_la_SOURCES = \
	class.c
libcutie_la_LIBADD = @LIBOBJS@

libcutie_std_la_SOURCES = \
	mem.c \
	panic.c \
	str.c
libcutie_std_la_LIBADD = @LIBOBJS@

CLEANFILES = \
	config.h.in~ \
	cutie.h.in~ \
	*.gcda \
	*.gcno \
	*.gcov

nobase_include_HEADERS = \
	cutie.h

