
# predictable - A linux kernel module example

`predictable` is a small Linux kernel module which makes it possible to read
a predictable sequence of numbers from `/proc/predictable`.

Run

    libcutie$ ./configure && make && make check && make amalgamation

and copy `libcutie/cutie.h` and `libcutie/cutie.c` to this directory. You can
then test the module by running:

    libcutie/examples/predictable$ make check

Observe: It is recommended that you do NOT try this on a machine important to
you. Use a virtual machine if possible.

