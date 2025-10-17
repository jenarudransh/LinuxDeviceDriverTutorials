// server.c - A FIFO (Named Pipe) example

#include <stdio.h>      // For printf(), perror()
#include <stdlib.h>     // For exit()
#include <unistd.h>     // For read(), close()
#include <string.h>     // For strcmp(), strlen()
#include <fcntl.h>      // For open() and O_RDONLY
#include <sys/stat.h>   // For mkfifo() and mode constants
#include <sys/types.h>  // For mkfifo()
#include <errno.h>      // For checking the 'errno' variable

#define FIFO_FILE "MYFIFO2"

int main() {
    int fd;
    char readbuf[80];
    int read_bytes;

    // Create the FIFO if it does not exist.
    // mkfifo is the modern, preferred function.
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        // If the error is that the file already exists, we can ignore it.
        if (errno != EEXIST) {
            perror("mkfifo failed");
            exit(1);
        }
    }

    printf("Server is waiting for a client...\n");

    // Open the FIFO for reading only.
    // This call will block until a client opens the FIFO for writing.
    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }

    printf("Client connected. Reading from FIFO...\n");

    // Loop until the client closes its end of the pipe (read returns 0)
    // or an error occurs (read returns -1).
    while ((read_bytes = read(fd, readbuf, sizeof(readbuf))) > 0) {
        // Null-terminate the string received
        readbuf[read_bytes] = '\0';
        
        printf("Received: \"%s\"\n", readbuf);

        // Check if the client sent the "end" command to terminate the server.
        if (strcmp(readbuf, "end") == 0) {
            printf("'end' command received. Shutting down.\n");
            break; // Exit the loop
        }
    }

    if (read_bytes == 0) {
        printf("Client closed the connection.\n");
    } else if (read_bytes == -1) {
        perror("read failed");
    }

    // Clean up
    close(fd);
    unlink(FIFO_FILE); // Remove the FIFO file from the system

    return 0;
}
