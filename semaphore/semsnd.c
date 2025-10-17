// semsnd.c - The writer process

#include <stdio.h>      // For printf(), perror()
#include <stdlib.h>     // For exit()
#include <unistd.h>     // For sleep()
#include <sys/ipc.h>    // For IPC functions (key_t)
#include <sys/sem.h>    // For semaphore functions
#include <sys/shm.h>    // For shared memory functions

#define SEM_KEY 11      // Key for the semaphore
#define SHM_KEY 100     // Key for the shared memory

int main() {
    int semid, shmid;
    int *shm_ptr;
    struct sembuf sb; // Semaphore buffer for operations

    // --- 1. Get and initialize the semaphore ---
    // Get a semaphore set with 1 semaphore. Create if it doesn't exist.
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }
    
    // Initialize semaphore at index 0 to 1 (unlocked/available).
    // This is often done by only one process, but it's safe to run multiple times.
    semctl(semid, 0, SETVAL, 1);

    printf("Semaphore created/initialized. semid: %d\n", semid);

    // --- 2. Lock the semaphore ---
    printf("Waiting to lock the semaphore...\n");
    sb.sem_num = 0;      // Operate on the first semaphore (index 0)
    sb.sem_op = -1;      // Decrement by 1 (lock/wait operation)
    sb.sem_flg = 0;      // No flags
    if (semop(semid, &sb, 1) == -1) {
        perror("semop lock failed");
        exit(1);
    }
    printf("Semaphore locked.\n");

    // --- 3. Access the shared resource (shared memory) ---
    // Get a shared memory segment of 50 bytes.
    shmid = shmget(SHM_KEY, 50, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to the shared memory.
    shm_ptr = (int *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }
    
    printf("Attached to shared memory. shmid: %d\n", shmid);

    // Write data to the shared memory.
    printf("Writing data to shared memory...\n");
    for (int i = 0; i < 5; i++) {
        shm_ptr[i] = i * 10; // Write values 0, 10, 20, 30, 40
    }
    printf("Data written. Holding lock for 10 seconds...\n");
    sleep(10); // Hold the lock to allow the reader to try and fail

    // Detach from shared memory.
    shmdt(shm_ptr);

    // --- 4. Unlock the semaphore ---
    printf("Unlocking the semaphore...\n");
    sb.sem_op = 1; // Increment by 1 (unlock/signal operation)
    if (semop(semid, &sb, 1) == -1) {
        perror("semop unlock failed");
        exit(1);
    }
    printf("Semaphore unlocked.\n");

    return 0;
}
