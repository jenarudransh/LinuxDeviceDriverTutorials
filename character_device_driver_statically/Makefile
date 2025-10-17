obj-m := allocating_major_number.o

KERNELDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

# CORRECT
default:
	make -C $(KERNELDIR) M=$(PWD) modules
