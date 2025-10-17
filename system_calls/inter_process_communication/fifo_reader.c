#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    const char *fifo = "/tmp/my_fifo_demo";
    if (mkfifo(fifo, 0666) == -1) { /* ignore if exists */ }

    int fd = open(fifo, O_RDONLY);
    if (fd < 0) { perror("open reader"); return 1; }
    char buf[256];
    ssize_t n = read(fd, buf, sizeof(buf)-1);
    if (n >= 0) {
        buf[n] = '\0';
        printf("Reader: got '%s'\n", buf);
    } else perror("read");
    close(fd);
    // Optionally remove FIFO
    // unlink(fifo);
    return 0;
}
