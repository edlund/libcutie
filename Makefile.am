
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	source \
	example \
	test \
	tool

CLEANFILES = \
	cutie.c \
	cutie.h

amalgamation:
	$(top_srcdir)/tool/amalgamate/amalgamate.py \
		--config $(top_srcdir)/cutie.h.json
	$(top_srcdir)/tool/amalgamate/amalgamate.py \
		--config $(top_srcdir)/cutie.c.json

clean-local:
	rm -rf dox/*

