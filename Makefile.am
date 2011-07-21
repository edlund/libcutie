
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	cutie \
	examples \
	tests

CLEANFILES = \
	cutie.c \
	cutie.h

amalgamation:
	export \
		top_srcdir=$(top_srcdir) \
		top_builddir=$(top_builddir) \
	&& $(top_srcdir)/tools/amalgamate.sh

clean-local:
	rm -rf dox/*

