#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int write_fifo(const char *fifo_path, const char *message) {
    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
}

int read_fifo(const char *fifo_path) {
    char buffer[128];
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0';  // Null-terminate the string
    printf("Received: %s\n", buffer);
    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <filepath> <r/w> [message]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filepath = argv[1];
    const char *mode = argv[2];

    

    if (strcmp(mode, "-w") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Message required for write mode\n");
            exit(EXIT_FAILURE);
        }
        const char *message = argv[3];
        write_fifo(filepath, message);
    } else if (strcmp(mode, "-r") == 0) {
        read_fifo(filepath);
    } else {
        fprintf(stderr, "Invalid mode: %s\n", mode);
        exit(EXIT_FAILURE);
    }

    return 0;
}
