#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "userFIFO"

int main() {
    int fd;
    char sendBuffer[200];
    char recvBuffer[200];

    while (1) {
        // User2 waits to receive a message
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        read(fd, recvBuffer, sizeof(recvBuffer));
        close(fd);

        printf("User2 received: %s\n", recvBuffer);

        // User2 sends a message
        printf("User2: Enter a message to send: ");
        fgets(sendBuffer, sizeof(sendBuffer), stdin);
        sendBuffer[strcspn(sendBuffer, "\n")] = '\0'; // Remove newline character

        fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        write(fd, sendBuffer, strlen(sendBuffer) + 1);
        close(fd);
    }

    return 0;
}