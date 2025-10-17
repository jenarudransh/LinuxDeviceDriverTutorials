// semrcv.c - The reader process

#include <stdio.h>      // For printf(), perror()
#include <stdlib.h>     // For exit()
#include <unistd.h>     // For sleep()
#include <sys/ipc.h>    // For IPC functions (key_t)
#include <sys/sem.h>    // For semaphore functions
#include <sys/shm.h>    // For shared memory functions

#define SEM_KEY 11      // Key for the semaphore (must match the sender)
#define SHM_KEY 100     // Key for the shared memory (must match the sender)

int main() {
    int semid, shmid;
    int *shm_ptr;
    struct sembuf sb; // Semaphore buffer for operations

    // --- 1. Get the existing semaphore ---
    // Get the semaphore set created by the sender.
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }
    printf("Attached to semaphore. semid: %d\n", semid);

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
    // Get the existing shared memory segment.
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

    // Read data from the shared memory.
    printf("Reading data from shared memory:\n");
    for (int i = 0; i < 5; i++) {
        // Use array indexing to avoid modifying the base pointer
        printf("  Value at index %d = %d\n", i, shm_ptr[i]);
    }

    // Detach from shared memory using the original pointer.
    shmdt(shm_ptr);

    // --- 4. Unlock the semaphore ---
    printf("Unlocking the semaphore...\n");
    sb.sem_op = 1; // Increment by 1 (unlock/signal operation)
    if (semop(semid, &sb, 1) == -1) {
        perror("semop unlock failed");
        exit(1);
    }
    printf("Semaphore unlocked.\n");

    // --- 5. Clean up IPC resources ---
    // This is optional but good practice. The last process to finish should clean up.
    printf("Cleaning up semaphore and shared memory...\n");
    semctl(semid, 0, IPC_RMID); // Remove the semaphore
    shmctl(shmid, IPC_RMID, NULL); // Remove the shared memory segment

    return 0;
}
