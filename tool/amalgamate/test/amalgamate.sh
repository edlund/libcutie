#!/bin/bash

function test_amalgamation {
	FILE=$1
	CONFIG_FILE="${FILE}.json"
	EXPECTED_FILE="${FILE}.expected"
	GENERATED_FILE="${FILE}"
	
	../amalgamate.py -c $CONFIG_FILE
	
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

cc -o source.out source.c && ./source.out
rm -f source.out

