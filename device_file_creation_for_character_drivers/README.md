🛠️ Prerequisites

To compile and run this module, you'll need a Linux system with the necessary build tools and kernel headers. On Debian-based systems like Ubuntu, you can install these with:
Bash

sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)

🚀 How to Build and Run

Follow these steps in your terminal from the root of the repository.

1. Build the Module

Use the provided Makefile to compile the device_file.c source code. This will generate the kernel module file, device_file.ko.
Bash

make

2. Load the Kernel Module

Insert the compiled module into the kernel using the insmod command. This requires superuser privileges.
Bash

sudo insmod device_file.ko

3. Verify the Device File

Check that the device file has been automatically created in the /dev directory.
Bash

ls -l /dev/etx_device

You can also view the kernel's message buffer with dmesg to see the log messages from the driver confirming its successful initialization.
Bash

dmesg | tail

4. Unload the Kernel Module

Remove the module from the kernel using the rmmod command. The module's name is the base of the file name (without .ko).
Bash

sudo rmmod device_file

5. Verify the Cleanup

Confirm that the device file has been automatically removed from the /dev directory. The ls command should now show that the file doesn't exist. You can also check dmesg again to see the exit message.
