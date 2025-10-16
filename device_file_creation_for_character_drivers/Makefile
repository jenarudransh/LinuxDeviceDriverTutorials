obj-m := device_file.o

KERNELDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

# CORRECT
default:
	make -C $(KERNELDIR) M=$(PWD) modules
