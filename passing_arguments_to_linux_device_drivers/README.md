Passing Arguments to a Linux Kernel Module

This tutorial demonstrates how to pass parameters to a Linux kernel module when it is loaded using the insmod command. This is a powerful feature that allows you to configure your driver's behavior at runtime without needing to recompile the source code.

For example, you could pass a GPIO pin number, a default timeout value, or an initial mode for your device.

## The Core Concept: module_param()

The mechanism for this is the module_param() macro, which is defined in <linux/moduleparam.h>. This macro creates an entry for your variable in the /sys/module/ directory, allowing its value to be set when the module is inserted.

The basic syntax is: module_param(variable_name, type, permissions);

    variable_name: The name of the variable in your C code that will store the value.

    type: The data type of the parameter (e.g., int for an integer, charp for a character pointer/string).

    permissions: The file permissions for the corresponding entry in /sys/module/your_module/parameters/. A value of S_IRUGO makes it readable by everyone, while 0644 makes it readable by everyone and writable only by the root user.

## How to Build and Run 🚀

This example (passing_arguments.c) is set up to accept an integer (my_value) and a string (my_string).

1. Compile the Driver

Navigate to this directory in your terminal and run the make command to compile the source code.
Bash

make

This will create the kernel module file: passing_arguments.ko.

2. Load the Module with Arguments

Use the sudo insmod command to load the driver into the kernel. You can now provide values for the parameters you defined.
Bash

# Example: Pass an integer and a string
sudo insmod passing_arguments.ko my_value=99 my_string="HelloFromUserspace"

If you don't provide a value, the driver will use the default value initialized in the C code.

3. Verify the Output

Check the kernel's message buffer with dmesg to see the values that the driver received.
Bash

dmesg | tail

You should see output similar to this, confirming that your arguments were passed successfully:

[timestamp] Value = 99
[timestamp] String = HelloFromUserspace
[timestamp] Kernel Module Inserted Successfully...

4. Check Parameters in sysfs (Optional)

After loading, you can view the parameters' current values directly via the sysfs filesystem.
Bash

cat /sys/module/passing_arguments/parameters/my_value
cat /sys/module/passing_arguments/parameters/my_string

5. Unload the Module

When you are finished, remove the module using the rmmod command.
Bash

sudo rmmod passing_arguments
