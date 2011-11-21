#!/bin/bash

# $srcdir is an environment variable set by automake.
echo "$0 srcdir=\"${srcdir}\""

function test_amalgamation {
	FILE=$1
	CONFIG_FILE="${srcdir}/${FILE}.json"
	PROLOGUE_FILE="${srcdir}/${FILE}.prologue"
	EXPECTED_FILE="${srcdir}/${FILE}.expected"
	GENERATED_FILE="${FILE}"
	
	"${srcdir}/../amalgamate.py" \
		"--config=${CONFIG_FILE}" \
		"--source=${srcdir}" \
		"--prologue=${PROLOGUE_FILE}"
	
	DIFF=`diff -Nur ${EXPECTED_FILE} ${GENERATED_FILE}`
	if [ "${DIFF}" ]; then
		echo "*** TEST FAILURE ***" 1>&2
		echo "Unexpected diff:" 1>&2
		echo "${DIFF}" 1>&2
		exit 1
	fi
}

test_amalgamation "include.h" > /dev/null
test_amalgamation "source.c" > /dev/null

function test_command {
	CMD=$1
	MSG=$2
	`${CMD}`
	if [ ! $? -eq 0 ]; then
		echo "*** TEST FAILURE ***" 1>&2
		echo "Command failed: ${CMD}" 1>&2
		exit 1
	fi
}

test_command "cc -o source.out source.c"
test_command "./source.out"

rm -f source.out

