#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) { // child
        printf("Child (%d): exiting immediately -> will become zombie until parent reaps.\n", getpid());
        exit(0);
    } else { // parent
        printf("Parent (%d): child pid=%d. Sleeping 20s so you can inspect with 'ps'.\n", getpid(), pid);
        sleep(20); // during this time child is a zombie (check with ps -l or ps aux | grep Z)
        printf("Parent: now calling wait() to reap child.\n");
        wait(NULL);
        printf("Parent: child reaped, exiting.\n");
    }
    return 0;
}
