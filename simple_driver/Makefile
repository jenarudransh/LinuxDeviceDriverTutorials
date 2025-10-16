obj-m := hello_world_module.o

KERNELDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

# CORRECT
default:
	make -C $(KERNELDIR) M=$(PWD) modules
