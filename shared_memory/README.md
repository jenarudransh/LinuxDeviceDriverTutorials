IPC: System V Shared Memory Example

This directory contains a C example demonstrating Inter-Process Communication (IPC) using System V shared memory. Shared memory is the fastest form of IPC because the kernel maps a memory segment into the address space of multiple processes. This allows processes to read and write to the same memory location directly, without involving the kernel in the data transfer itself.

This example uses a client-server model:

    server: A server program that creates a shared memory segment, writes data into it, and waits for a client.

    client: A client program that attaches to the same shared memory segment, reads the data written by the server, and then detaches.

## How it Works 🧠

Instead of passing data through the kernel (like with pipes or message queues), shared memory allows processes to access the same block of RAM. One process creates the segment, and other processes can "attach" to it. Synchronization between processes (e.g., ensuring one process doesn't read while another is writing) must be handled separately, often using semaphores.

The key system calls used are:

    shmget(): Creates a new shared memory segment or gets the ID of an existing one.

    shmat(): Attaches the shared memory segment to the process's address space.

    shmdt(): Detaches the segment from the process's address space.

    shmctl(): Performs control operations, such as marking the segment for deletion.

## How to Compile and Run 🚀

You will need two separate terminal windows to run this client-server demo.

1. Compile the Programs

First, compile both the client and server C files using gcc.
Bash

# Compile the server program
gcc server.c -o server

# Compile the client program
gcc client.c -o client

2. Run the Server

In your first terminal, start the server program. It will create the shared memory segment, write a message into it, and then wait for the client to read it.
Bash

./server

The server will print a message and then wait:

Data written in memory: Hello from the other side!
Waiting for client...

3. Run the Client

In your second terminal, run the client program. It will attach to the memory segment, read the data, and print it.
Bash

./client

The client will read the data and print it:

Data read from memory: Hello from the other side!

4. Check the Result

After the client runs, go back to your first terminal. You will see that the server detected the client's action and has now finished its execution and cleaned up the memory segment.

## Cleaning Up (Important!)

System V shared memory segments are persistent and will remain in the kernel until they are explicitly removed. This example's server program is designed to clean up after itself, but it's good practice to know how to do it manually.

    List active shared memory segments:
    Bash

ipcs -m

Remove a specific segment by its ID (use the shmid from the command above):
Bash

ipcrm -m <shmid>
