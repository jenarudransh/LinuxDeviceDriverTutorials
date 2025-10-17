#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        // child: increase niceness (lower priority)
        printf("Child (%d): current nice = %d\n", getpid(), nice(0));
        int n = nice(10); // add 10 to niceness
        printf("Child (%d): new nice = %d\n", getpid(), n);
        for (long i=0;i<5;i++) {
            printf("Child: working %ld\n", i);
            sleep(1);
        }
        exit(0);
    } else {
        // parent: lower niceness (higher priority) attempt (may require privileges)
        printf("Parent (%d): current nice = %d\n", getpid(), nice(0));
        // try to set higher priority (reduce nice) using setpriority
        if (setpriority(PRIO_PROCESS, getpid(), -5) == 0) {
            printf("Parent: setpriority succeeded, new nice = %d\n", nice(0));
        } else {
            perror("setpriority (may require root)");
            printf("Parent: nice remains %d\n", nice(0));
        }
        for (int i=0;i<5;i++) {
            printf("Parent: working %d\n", i);
            sleep(1);
        }
        wait(NULL);
    }
    return 0;
}
