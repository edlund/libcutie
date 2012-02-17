
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	source \
	example \
	test

CLEANFILES = \
	cutie.c \
	cutie.h

amalgamation:
	amalgamate.py --config=$(top_srcdir)/cutie.h.json --source=$(top_srcdir) \
		--prologue=$(top_srcdir)/prologue.h --verbose=yes
	amalgamate.py --config=$(top_srcdir)/cutie.c.json --source=$(top_srcdir) \
		--prologue=$(top_srcdir)/prologue.h --verbose=yes

clean-local:
	rm -rf dox/*

