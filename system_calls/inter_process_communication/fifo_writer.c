#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    const char *fifo = "/tmp/my_fifo_demo";
    // create FIFO if not exists
    if (mkfifo(fifo, 0666) == -1) {
        // ignore error if exists
    }

    int fd = open(fifo, O_WRONLY);
    if (fd < 0) { perror("open writer"); return 1; }
    const char *msg = "Message from writer (FIFO)";
    write(fd, msg, strlen(msg));
    close(fd);
    printf("Writer: wrote message and exited\n");
    return 0;
}
