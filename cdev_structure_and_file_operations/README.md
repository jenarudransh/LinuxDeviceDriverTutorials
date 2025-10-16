🛠️ Prerequisites

To build and run this driver, you'll need:

    A Linux system (e.g., Ubuntu, Debian, Raspberry Pi OS).

    The kernel headers for your currently running kernel. You can usually install these with:
    Bash

sudo apt-get install linux-headers-$(uname -r)

Standard build tools (make, gcc). You can install them with:
Bash

    sudo apt-get install build-essential

🚀 How to Use

1. Build the Driver

Navigate to the project directory in your terminal and run the make command. This will compile dummy_driver.c and create the kernel module file dummy_driver.ko.
Bash

make

To clean up the build files, you can run make clean.

2. Load the Kernel Module

Insert the compiled module into the kernel using the insmod command.
Bash

sudo insmod dummy_driver.ko

After loading, you can verify that the module is active and that the device file has been created.
Bash

# Check if the module is loaded
lsmod | grep dummy_driver

# Check if the device file exists
ls -l /dev/etx_device

3. Interact with the Device

You can trigger the driver's file operations using standard command-line tools.

    To test open, write, and release:
    Bash

echo "Hello from user space" > /dev/etx_device

To test open, read, and release:
Bash

    cat /dev/etx_device

4. Check the Output

The driver's output is sent to the kernel's log ring buffer. You can view these messages using the dmesg command.
Bash

dmesg

You should see output similar to this:

[timestamp] Major = 246 Minor = 0 
[timestamp] Device Driver Insert...Done!!!
[timestamp] Driver Open Function Called...!!!
[timestamp] Driver Write Function Called...!!!
[timestamp] Driver Release Function Called...!!!
[timestamp] Driver Open Function Called...!!!
[timestamp] Driver Read Function Called...!!!
[timestamp] Driver Release Function Called...!!!

5. Unload the Kernel Module

When you are finished, you can remove the module from the kernel using the rmmod command. This will also clean up the device file.
Bash

sudo rmmod dummy_driver

You can check dmesg again to see the "Device Driver Remove...Done!!!" message.

📜 License

This project is licensed under the GNU General Public License (GPL).
