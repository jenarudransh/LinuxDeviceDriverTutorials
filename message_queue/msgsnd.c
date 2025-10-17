// msgsnd.c

#include <stdio.h>      // For printf() and perror()
#include <stdlib.h>     // For exit()
#include <string.h>     // For strcpy()
#include <sys/ipc.h>    // For IPC functions (like key_t)
#include <sys/msg.h>    // For message queue functions

// Define the message buffer structure
// The mtype member MUST be of type 'long'
struct msg_buffer {
    long mtype;
    char mtext[50];
};

int main() {
    struct msg_buffer m; // Declare the message buffer variable inside main
    
    key_t key = 20;
    int msqid = msgget(key, IPC_CREAT | 0666);

    if (msqid == -1) {
        perror("msgget failed");
        exit(1);
    }
    
    printf("Message Queue Ready to Send. msqid: %d\n", msqid);

    // --- Send first message (type 80) ---
    m.mtype = 80;
    strcpy(m.mtext, "dell");
    
    // The size should be for the text part only, not the whole struct
    if (msgsnd(msqid, &m, sizeof(m.mtext), 0) == -1) {
        perror("msgsnd for type 80 failed");
        exit(1);
    }
    
    printf("1st message sent successfully (type %ld): '%s'\n", m.mtype, m.mtext);

    // --- Send second message (type 90) ---
    m.mtype = 90;
    strcpy(m.mtext, "Hello");

    if (msgsnd(msqid, &m, sizeof(m.mtext), 0) == -1) {
        perror("msgsnd for type 90 failed");
        exit(1);
    }
    
    printf("2nd message sent successfully (type %ld): '%s'\n", m.mtype, m.mtext);

    return 0;
}
