// msgrcv.c

#include <stdio.h>      // For printf() and perror()
#include <stdlib.h>     // For exit()
#include <sys/ipc.h>    // For IPC functions (like key_t)
#include <sys/msg.h>    // For message queue functions

// Define the message buffer structure
// The mtype member MUST be of type 'long'
struct msg_buffer {
    long mtype;
    char mtext[50];
};

int main() {
    struct msg_buffer m; // Declare the message buffer variable
    
    key_t key = 20;
    int msqid = msgget(key, IPC_CREAT | 0666);

    if (msqid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Message Queue Ready to Receive. msqid: %d\n", msqid);

    // --- Receive first message (type 80) ---
    // This call will block (wait) until a message of type 80 arrives.
    int rcv = msgrcv(msqid, &m, sizeof(m.mtext), 80, 0);

    if (rcv == -1) {
        perror("msgrcv for type 80 failed");
        exit(1);
    } else {
        printf("Message received (type 80): %s\n", m.mtext);
    }

    // --- Receive second message (type 90) ---
    // This call will block until a message of type 90 arrives.
    int rcv1 = msgrcv(msqid, &m, sizeof(m.mtext), 90, 0);

    if (rcv1 == -1) {
        perror("msgrcv for type 90 failed");
        exit(1);
    } else {
        printf("Message received (type 90): %s\n", m.mtext);
    }

    return 0;
}
