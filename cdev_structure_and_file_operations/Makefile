obj-m := dummy_driver.o

KERNELDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

# CORRECT
default:
	make -C $(KERNELDIR) M=$(PWD) modules
