AC_INIT([cutie], [0.0.1], [erik.o.edlund@gmail.com])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AC_PROG_CPP
AC_LANG(C)
AM_PATH_PYTHON([2.7])
LT_INIT

AC_ARG_WITH([check],
	[AC_HELP_STRING([--with-check=DIR],
		[check install directory])],
	[
		CFLAGS="-I$withval/include $CFLAGS"
		LDFLAGS="-L$withval/lib $LDFLAGS"
	],
	[])

AC_CHECK_HEADER([check.h], [], [AC_MSG_ERROR(
	[Could not find Check unit test framework.])])

AC_CHECK_HEADER([execinfo.h],
	[HAVE_EXECINFO_H=1],
	[HAVE_EXECINFO_H=0])
AC_SUBST(HAVE_EXECINFO_H)

AC_ARG_ENABLE([aliases],
	[AC_HELP_STRING([--enable-aliases],
		[aliases for commonly used macros [default=yes]])],
	[
		case $enableval in
			yes) ENABLE_ALIASES=1 ;;
			no) ENABLE_ALIASES=0 ;;
			*) AC_MSG_ERROR([bad value for --enable-aliases: yes or no])
		esac
	],
	[ENABLE_ALIASES=1])
AC_SUBST(ENABLE_ALIASES)

AC_ARG_ENABLE([abstract],
	[AC_HELP_STRING([--enable-abstract],
		[support abstract methods [default=yes]])],
	[
		case $enableval in
			yes) ENABLE_ABSTRACT=1 ;;
			no) ENABLE_ABSTRACT=0 ;;
			*) AC_MSG_ERROR([bad value for --enable-abstract: yes or no])
		esac
	],
	[ENABLE_ABSTRACT=1])
AC_SUBST(ENABLE_ABSTRACT)

AC_ARG_ENABLE([memzero-new],
	[AC_HELP_STRING([--enable-memzero-new],
		[zero new objects [default=yes]])],
	[
		case $enableval in
			yes) ENABLE_MEMZERO_NEW=1 ;;
			no) ENABLE_MEMZERO_NEW=0 ;;
			*) AC_MSG_ERROR([bad value for --enable-memzero-new: yes or no])
		esac
	],
	[ENABLE_MEMZERO_NEW=1])
AC_SUBST(ENABLE_MEMZERO_NEW)

AC_DEFINE([ENABLE_CHECK_FORK], [],
	[Define to one to 1 to run tests in a separate address space])
AC_ARG_ENABLE([check_fork],
	[AC_HELP_STRING([--enable-check-fork],
		[run tests in a separate address space [default=yes]])],
	[
		case $enableval in
			yes) AC_DEFINE_UNQUOTED([ENABLE_CHECK_FORK], [1]) ;;
			no) AC_DEFINE_UNQUOTED([ENABLE_CHECK_FORK], [0]) ;;
			*) AC_MSG_ERROR([bad value for --enable-check-fork: yes or no])
		esac
	],
	[AC_DEFINE_UNQUOTED([ENABLE_CHECK_FORK], [1])])

AC_ARG_ENABLE(gcov,
	AC_HELP_STRING([--enable-gcov],
		[turn on test coverage [default=no]]),
	[
		case $enableval in
			yes) ENABLE_GCOV=true ;;
			no) ENABLE_GCOV=false ;;
			*) AC_MSG_ERROR([bad value for --enable-gcov: yes or no])
		esac
	],
	[ENABLE_GCOV=false])
if test x$ENABLE_GCOV = xtrue ; then
	GCOV_CFLAGS="-fprofile-arcs -ftest-coverage"
	AC_SUBST(GCOV_CFLAGS)
fi
AM_CONDITIONAL(ENABLE_GCOV, test x"$ENABLE_GCOV" = "xtrue")

AC_CONFIG_HEADERS([cutie/config.h])
AC_CONFIG_FILES([
	Makefile
	cutie/Makefile
	examples/Makefile
	examples/robots/Makefile
	tests/Makefile
	cutie/cutie.h])
AC_OUTPUT

