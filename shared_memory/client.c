// client.c - A FIFO (Named Pipe) example

#include <stdio.h>      // For printf(), fgets(), perror()
#include <stdlib.h>     // For exit()
#include <unistd.h>     // For write(), close()
#include <string.h>     // For strcmp(), strlen(), strcspn()
#include <fcntl.h>      // For open() and O_WRONLY
#include <sys/types.h>  // For basic system data types
#include <sys/stat.h>   // For FIFO constants

#define FIFO_FILE "MYFIFO2"

int main() {
    int fd;
    char writebuf[80];

    // Open the FIFO for writing only.
    // The server must be running and have already created the FIFO.
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("Client cannot open FIFO");
        exit(1);
    }

    printf("Client connected. Enter text to send (type 'end' to quit):\n");

    // Loop to get user input and write it to the server.
    while (1) {
        printf("> ");
        // Read a line of text from the user's keyboard.
        if (fgets(writebuf, sizeof(writebuf), stdin) == NULL) {
            break; // Exit on input error (e.g., Ctrl+D)
        }

        // Remove the trailing newline character that fgets() adds.
        writebuf[strcspn(writebuf, "\n")] = 0;

        // Write the user's message to the FIFO.
        if (write(fd, writebuf, strlen(writebuf)) == -1) {
            perror("write to FIFO failed");
            break; // Exit loop on write error
        }

        // If the user typed "end", exit the loop.
        if (strcmp(writebuf, "end") == 0) {
            break;
        }
    }

    // Clean up
    close(fd);
    printf("Client disconnected.\n");

    return 0;
}
