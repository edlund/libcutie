#!/bin/bash

# Generate check.data which is used by check.py to verify
# that the result given by predictable.ko (given a known
# seed) is actually predictable.

if [ -z $1 ]; then
	echo "Usage: $0 <number>"
	exit 1
fi
make
sudo insmod predictable.ko
rm -f check.data
for i in `seq 1 $1`; do
	cat /proc/predictable >> check.data
	echo "" >> check.data
done
sudo rmmod predictable
sudo -k

