# Linux Process Management and IPC Tutorials

This repository contains a collection of C programs demonstrating fundamental concepts of process management and Inter-Process Communication (IPC) in a Linux environment. It also includes basic examples of "Hello World" Linux Kernel Modules.

This code is intended for educational purposes to understand how various system calls work for process control, synchronization, and communication.

## Prerequisites

Before you begin, ensure you have the following installed on your Ubuntu/Debian-based system.

* **Build Tools**: For compiling C code.
    ```bash
    sudo apt update
    sudo apt install build-essential
    ```
* **Kernel Headers**: Required for compiling the Linux device drivers.
    ```bash
    sudo apt install linux-headers-$(uname -r)
    ```

---

## How to Compile and Run

Each example is located in its own directory. Navigate into a specific directory to compile and run the programs.

### 1. Process Management & Signals

These examples demonstrate `fork()`, `exec()`, `wait()`, zombie/orphan processes, and signal handling.

* **Compilation**:
    ```bash
    gcc <program_name>.c -o <executable_name>
    ```
    *(Example: `gcc process_creation.c -o process_creation`)*

* **Execution**:
    ```bash
    ./<executable_name>
    ```

* **To observe a zombie process**:
    1.  Run `./zombie_maker`.
    2.  In a **second terminal**, run `ps aux | grep 'Z'`. You will see the child process with a `Z` status.

### 2. Inter-Process Communication (IPC)

These examples require running two programs in two separate terminals.

#### **FIFOs (Named Pipes)**
The server must be started first. It will wait for the client to connect.

1.  **Compile**:
    ```bash
    # In one terminal
    gcc server.c -o server

    # In a second terminal
    gcc client.c -o client
    ```
2.  **Execution**:
    ```bash
    # In terminal 1, run the server
    ./server

    # In terminal 2, run the client
    ./client
    ```
    Now you can type messages in the client terminal and see them appear in the server terminal. Type `end` to quit.

#### **Message Queues**
The receiver must be started first to create the queue and wait for messages.

1.  **Compile**:
    ```bash
    gcc msgsnd.c -o sender
    gcc msgrcv.c -o receiver
    ```
2.  **Execution**:
    ```bash
    # In terminal 1, run the receiver
    ./receiver

    # In terminal 2, run the sender
    ./sender
    ```

#### **Shared Memory with Semaphores**
The sender (writer) locks the semaphore, writes to shared memory, and sleeps before unlocking. The receiver (reader) will wait until the sender releases the lock.

1.  **Compile**:
    ```bash
    gcc semsnd.c -o sender
    gcc semrcv.c -o receiver
    ```
2.  **Execution**:
    ```bash
    # In terminal 1, run the sender
    ./sender

    # While the sender is sleeping, run the receiver in terminal 2
    ./receiver
    ```
    The receiver will wait, then read the data and clean up the IPC resources.

### 3. Linux Kernel Modules

These examples demonstrate basic character device drivers.

1.  **Compilation**:
    Navigate into the driver's directory and run the `make` command.
    ```bash
    make
    ```
    This will produce a `<module_name>.ko` file.

2.  **Execution**:
    * **Load the module**:
        ```bash
        sudo insmod <module_name>.ko
        ```
    * **Check kernel messages**:
        ```bash
        dmesg
        ```
    * **Unload the module**:
        ```bash
        sudo rmmod <module_name>
        ```
    * **Clean up build files**:
        ```bash
        make clean
        ```

---

## Concepts Demonstrated

* **Process Control**: `fork()`, `exec()`, `wait()`, `getpid()`, `getppid()`
* **Process States**: Zombie and Orphan processes.
* **Synchronization**: Semaphores (`semget`, `semop`, `semctl`).
* **Inter-Process Communication (IPC)**:
    * Pipes (Unnamed)
    * FIFOs (Named Pipes)
    * Message Queues (`msgget`, `msgsnd`, `msgrcv`)
    * Shared Memory (`shmget`, `shmat`, `shmdt`)
* **Kernel Development**: Basic character device drivers, `module_init`, `module_exit`.
