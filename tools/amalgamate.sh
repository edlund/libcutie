#!/bin/bash

# Simplistic helper script for creating a freestanding source
# file for libcutie. Do not call this script directly if you
# do not know exactly what you are doing, instead run
#     $ make amalgamation
# from your top build directory.

echo "Creating amalgamation..."
echo "top_srcdir=$top_srcdir"
echo "top_builddir=$top_builddir"

if [ -z $top_srcdir ] || [ -z $top_builddir ]; then
	echo "Check top_srcdir and/or top_builddir"
	exit 1
fi

echo "Creating: $top_builddir/cutie.c"
echo "Creating: $top_builddir/cutie.h"

# Create the combined source file.
timestamp=`date +"%Y-%m-%d %H:%M"`
cat > $top_builddir/cutie.c <<EOF
/* libcutie amalgamation (https://github.com/edlund/libcutie)
 * Automatically generated $timestamp
 * 
 * This file is an amalgamation of cutie.c and cutie.h from
 * libcutie. It can be compiled as a freestanding source file
 * in projects using cutie (at least in theory).
 * 
 * To use the amalgamation in a project, you only need to
 * copy this file and cutie.h into your source tree and make
 * sure that it is compiled and linked. If you do not have a
 * copy of cutie.h you can create one using this file.
 */
#define CUTIE_STDC 0
#define CUTIE_AMALGAMATION 1

EOF
cat >> $top_builddir/cutie.c \
	$top_builddir/cutie/cutie.h \
	$top_srcdir/cutie/cutie.c

cp $top_builddir/cutie/cutie.h $top_builddir/cutie.h

echo "... done!"

