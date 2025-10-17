#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void sigchld_handler(int signo) {
    // Reap any exited child(ren)
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("SIGCHLD: child %d exited with %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("SIGCHLD: child %d terminated abnormally\n", pid);
        }
    }
}

void sigint_handler(int signo) {
    printf("\nSIGINT received. Exiting master process.\n");
    exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) { perror("sigaction SIGCHLD"); }

    struct sigaction sa2;
    sa2.sa_handler = sigint_handler;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;
    if (sigaction(SIGINT, &sa2, NULL) == -1) { perror("sigaction SIGINT"); }

    printf("Master PID=%d. Press Ctrl-C to exit.\n", getpid());

   // spawn a few short-lived children
    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Child %d: sleeping %d seconds then exit\n", getpid(), i+1);
            sleep(i+1);
            _exit(i+10);
        }
    }

    // main loop: do other work while children run
    for (;;) {
        printf("Master: doing work (sleeping 1s)...\n");
        sleep(1);
    }
    return 0;
}
