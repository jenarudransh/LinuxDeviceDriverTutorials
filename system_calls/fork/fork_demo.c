#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child
        printf("Child: pid=%d, ppid=%d\n", getpid(), getppid());
        sleep(1);
        printf("Child: exiting\n");
    } else {
        // Parent
        printf("Parent: pid=%d, child pid=%d\n", getpid(), pid);
        printf("Parent: waiting a bit before exiting\n");
        sleep(2);
        printf("Parent: exiting\n");
    }
    return 0;
}
