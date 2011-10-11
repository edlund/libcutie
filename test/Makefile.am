
AM_CFLAGS = \
	-std=c99 \
	-Wall \
	-Werror \
	-Wextra \
	-pedantic \
	-I$(top_srcdir)/include \
	-D_GNU_SOURCE \
	-DCUTIE_CHECK=1 \
	-DTOP_SRCDIR=\"$(top_srcdir)\" \
	-DTOP_BUILDDIR=\"$(top_builddir)\" \
	@GCOV_CFLAGS@
AM_LDFLAGS = -lcheck

CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov

TESTS = \
	class \
	cpp \
	panic

check_PROGRAMS = \
	class \
	cpp \
	panic

class_SOURCES = \
	class.c \
	class_abstractgizmo.c \
	class_emptygizmo.c \
	class_widget.c \
	class_filewidget.c \
	class_integerwidget.c
class_LDADD = \
	$(top_builddir)/source/libcutie.la

cpp_SOURCES = \
	cpp.c
cpp_LDADD = \
	$(top_builddir)/source/libcutie.la

panic_SOURCES = \
	panic.c
panic_LDADD = \
	$(top_builddir)/source/libcutie.la

