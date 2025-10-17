#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        printf("Child: sleeping 3s then exit\n");
        sleep(3);
        exit(42);
    } else {
        printf("Parent: doing non-blocking poll for child (waitpid WNOHANG)\n");
        int status;
        pid_t r;
        while ((r = waitpid(pid, &status, WNOHANG)) == 0) {
            printf("Parent: child still running, doing other work...\n");
            sleep(1);
        }
        if (r == pid) {
            if (WIFEXITED(status)) {
                printf("Parent: child exited with code %d\n", WEXITSTATUS(status));
            }
        } else {
            perror("waitpid");
        }
    }
    return 0;
}
