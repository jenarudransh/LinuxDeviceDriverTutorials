#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        printf("Child: will exec 'ls -l /'\n");
        execlp("ls", "ls", "-l", "/", (char *)NULL);
        // if execlp returns, it failed
        perror("execlp");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent: child done running ls\n");
    }
    return 0;
}
