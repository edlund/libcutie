ccflags-y := -DCUTIE_KERNEL=CUTIE_KERNEL_LINUX

obj-m := predictable.o
predictable-y := \
	cutie.o \
	module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

check: all
	sudo -k $(PWD)/check.py

