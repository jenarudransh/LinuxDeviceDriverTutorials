📂 Project Files

1. Driver Code (allocating_major_number.c)

This file contains the C source code for our simple kernel module. It defines the init and exit functions that print messages to the kernel log upon loading and unloading.

2. Makefile

This file is used to compile the C code into a loadable kernel object (.ko) file.

🚀 How to Use

Follow these steps in your Linux terminal to compile and manage the driver.

1. Compile the Driver

Navigate to the project directory and run the make command. This will create the allocating_major_number.ko file.
Bash

make

2. Load the Module

Use the insmod command with root privileges to load the driver into the kernel.
Bash

sudo insmod allocating_major_number.ko

3. Check Kernel Messages

The printk() messages from the init function are sent to the kernel log buffer. View them using dmesg.
Bash

dmesg

You should see output similar to this:

[timestamp] Welcome to EmbeTronicX
[timestamp] This is the Simple Module
[timestamp] Kernel Module Inserted Successfully...

4. List Loaded Modules

Verify that your module is loaded using the lsmod command.
Bash

lsmod | grep allocating_major_number

5. Get Module Information

Inspect the module's metadata (author, license, etc.) using modinfo.
Bash

modinfo allocating_major_number.ko

6. Unload the Module

Remove the driver from the kernel using rmmod.
Bash

sudo rmmod allocating_major_number

7. Verify Unloading

Check dmesg again to see the message from the exit function.
Bash

dmesg

You should see the new message:

[timestamp] Kernel Module Removed Successfully...
