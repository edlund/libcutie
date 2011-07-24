
# cutie - C UTilitIEs

cutie is a minimalistic collection of utilities intended to facilitate object
oriented programming in C. The following OOP techniques are supported, the idea
is that they will provide the bare minimum required to comfortably do OOP in C:

 * Single inheritance.
 * Polymorphism.
 * Virtual methods (all methods are virtual).
 * Basic RTTI.
 * Object cloning.
 * Type safety (void or char pointers are rarely used).

In theory cutie is intended to be usable for kernel, device driver and other
forms of low-level development where C is a common language of choice and where
higher level languages supporting OOP mechanisms are unavailable. This idea has
heavily influenced cuties design and has resulted in a list of guidelines for
cuties core:

 * It must be fast.
 * It must be usable with a minimal libc implementation.
 * It must be usable without dynamic memory allocation.
 * It must be usable in a multi-threaded environment without requiring
   synchronization primitives for object initialization.

In practice cutie is still under development and is quite possibly useless.
It might never become useful for any real world scenario either.

## Compiling and installing cutie

You need the following things to successfully compile cutie:

 * An ISO C99 compiler and preprocessor:
   * gcc (4.4+), http://gcc.gnu.org/
   * clang (2.8+), http://clang.llvm.org/
 * GNU autotools, http://www.gnu.org/software/autoconf/
 * libtool, http://www.gnu.org/software/libtool/
 * Check unit test framework, http://check.sourceforge.net/
 * Python (2.7+)

Configuring, compiling, testing and installing cutie can then be as simple as:

    libcutie$ autoreconf -i
    libcutie$ ./configure && make && make check && sudo -k make install

You can then #include cutie.h and link with -lcutie. For more options, simply
run `./configure --help`.

## Getting started

Have a look at the examples/ and tests/.

## Uninstalling cutie

Use `make uninstall` to undo everything `make install` did:

    libcutie$ sudo -k make uninstall

