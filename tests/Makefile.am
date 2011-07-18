
AM_CFLAGS = \
	-std=c99 \
	-Wall \
	-Werror \
	-Wextra \
	-Wno-missing-field-initializers \
	-pedantic \
	-I$(top_srcdir)/cutie \
	-D_GNU_SOURCE \
	-D_CUTIE_CHECK=1 \
	-D_TOP_SRCDIR="\"$(top_srcdir)\"" \
	-D_TOP_BUILDDIR="\"$(top_builddir)\"" \
	@GCOV_CFLAGS@
AM_LDFLAGS = -lcheck

CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov

TESTS = \
	check_class \
	check_cpp \
	check_panic

check_PROGRAMS = \
	check_class \
	check_cpp \
	check_panic

check_class_SOURCES = check_class.c \
	check_class_abstractgizmo.c \
	check_class_emptygizmo.c \
	check_class_widget.c \
	check_class_filewidget.c \
	check_class_integerwidget.c
check_class_LDADD = \
	$(top_builddir)/cutie/libcutie.la

check_cpp_SOURCES = check_cpp.c
check_cpp_LDADD = \
	$(top_builddir)/cutie/libcutie.la

check_panic_SOURCES = check_panic.c
check_panic_LDADD = \
	$(top_builddir)/cutie/libcutie.la

