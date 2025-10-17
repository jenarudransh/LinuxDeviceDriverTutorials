#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) { // child
        sleep(2); // wait for parent to exit
        printf("Child (%d): parent is %d after parent's exit. Now orphaned.\n", getpid(), getppid());
        sleep(2);
        printf("Child: exiting\n");
        exit(0);
    } else { // parent
        printf("Parent (%d): exiting immediately, child pid=%d\n", getpid(), pid);
        exit(0); // parent exits right away -> child becomes orphan
    }
}
