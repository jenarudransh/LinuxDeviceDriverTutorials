Prerequisites

Before you begin, ensure you have the following installed on your Linux system (e.g., Ubuntu, Debian):

    build-essential (for make and GCC)

    linux-headers for your specific kernel version (e.g., sudo apt install linux-headers-$(uname -r))

How to Build and Run

1. Create a Makefile

You will need a Makefile in the same directory as allocating_major_number_dynamically.c to build the kernel module. Create a file named Makefile with the following content:
Makefile

obj-m += allocating_major_number_dynamically.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

2. Build the Driver

Open your terminal in the project directory and run the make command. This will compile the source code and generate a kernel module file named allocating_major_number_dynamically.ko.
Bash

make

3. Load the Driver

Insert the compiled module into the kernel using the insmod command. You'll need superuser privileges.
Bash

sudo insmod allocating_major_number_dynamically.ko

4. Verify the Driver

You can check that the driver was loaded successfully in a few ways:

    Check Kernel Messages: The dmesg command will show the print statements from the driver, including the dynamically allocated major number.
    Bash

dmesg | tail

You should see output similar to this:

[timestamp] Major = 243 Minor = 0
[timestamp] Kernel Module Inserted Successfully...

Check Registered Devices: You can see your driver's name and its major number listed in /proc/devices.
Bash

    cat /proc/devices | grep "rudransh_Dev"

    Example output:

    243 rudransh_Dev

5. Unload the Driver

When you are finished, remove the module from the kernel using the rmmod command.
Bash

sudo rmmod allocating_major_number_dynamically

You can again use dmesg to confirm that the module's exit function was called.

License

This project is licensed under the GNU General Public License (GPL).
