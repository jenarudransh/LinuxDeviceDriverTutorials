IPC: System V Semaphore Example

This directory contains a C example demonstrating Inter-Process Communication (IPC) using System V semaphores. Semaphores are a synchronization primitive used to control access to a shared resource by multiple processes, preventing race conditions and ensuring orderly execution.

This example consists of two programs:

    semsnd: A sender program that acquires or signals a semaphore.

    semrcv: A receiver program that waits for the semaphore to be released or signaled by the other process.

## How it Works 🚦

A semaphore is essentially an integer counter managed by the kernel. Processes can perform two primary operations on it: wait (decrement) and signal (increment).

    Wait (P operation): If the semaphore's value is greater than zero, it is decremented. If it is zero, the process blocks (waits) until the value becomes greater than zero.

    Signal (V operation): The semaphore's value is incremented. If other processes are waiting, one of them is unblocked.

This mechanism is perfect for protecting a "critical section"—a piece of code that only one process should execute at a time.

The key system calls used are:

    semget(): Creates a new semaphore set or gets the ID of an existing one.

    semop(): Performs operations (wait or signal) on the semaphores in a set.

    semctl(): Performs control operations, such as initializing or deleting the semaphore set.

## How to Compile and Run 🚀

You will need two separate terminal windows to see the synchronization in action.

1. Compile the Programs

First, compile both C files using gcc.
Bash

# Compile the sender program
gcc semsnd.c -o semsnd

# Compile the receiver program
gcc semrcv.c -o semrcv

2. Run the First Process

In your first terminal, run one of the programs. Let's start with the receiver. It will attempt to acquire the semaphore but will likely have to wait.
Bash

./semrcv

3. Run the Second Process

In your second terminal, run the sender program. This program will perform the corresponding signal operation, which will unblock the receiver process in the first terminal.
Bash

./semsnd

4. Observe the Result

After running semsnd in the second terminal, you will see the semrcv process in the first terminal unblock and complete its execution. This demonstrates how one process can wait for a signal from another.

## Cleaning Up (Important!)

Like other System V IPC objects, semaphores persist in the kernel until they are explicitly removed. It's good practice to clean them up after you're done.

    List active semaphore sets:
    Bash

ipcs -s

Remove a specific semaphore set by its ID (use the semid from the command above):
Bash

ipcrm -s <semid>
