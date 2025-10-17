This directory contains a classic C example of Inter-Process Communication (IPC) using System V message queues. It demonstrates how two independent processes can communicate by sending and receiving messages through a kernel-maintained queue.

The example consists of two separate programs:

    msgsnd: A sender program that creates a message and places it onto a message queue.

    msgrcv: A receiver program that retrieves the message from the same queue.

## How it Works ⚙️

Message queues are a way for processes to exchange data without having a direct connection. The kernel provides a public queue that processes can access using a unique key. One process writes a message to the queue, and another process can read it. The receiving process can be running at the same time or start up later.

The key system calls used in this example are:

    ftok(): Generates a unique key for the message queue.

    msgget(): Creates a new message queue or gets the ID of an existing one.

    msgsnd(): Sends a message to the queue.

    msgrcv(): Receives a message from the queue.

    msgctl(): Performs control operations, like deleting the queue.

## How to Compile and Run 🚀

You'll need two separate terminal windows to run this demo.

1. Compile the Programs

First, compile both the sender and receiver C files using gcc.
Bash

# Compile the sender program
gcc msgsnd.c -o msgsnd

# Compile the receiver program
gcc msgrcv.c -o msgrcv

2. Run the Receiver

In your first terminal, run the receiver program. It will create the message queue and then block (wait) until a message arrives.
Bash

./msgrcv

You will see an output like this, and then the cursor will wait:

Data received is: _________________

3. Run the Sender

In your second terminal, run the sender program. It will send a predefined message to the queue.
Bash

./msgsnd

The sender will print a confirmation message and exit:

Data send is : Hello from the other side!

4. Check the Result

Go back to your first terminal. You will see that the receiver has now received the message and printed it to the console before exiting.

Data received is: Hello from the other side!

## Cleaning Up (Important!)

System V IPC objects like message queues persist in the kernel even after the programs finish. You should periodically check for and remove them.

    List active message queues:
    Bash

ipcs -q

Remove a specific message queue by its ID (use the msqid from the command above):
Bash

ipcrm -q <msqid>
