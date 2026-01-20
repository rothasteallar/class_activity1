#include <stdio.h>
#include <fcntl.h>   // for open
#include <unistd.h>  // for read, write, close
#include <stdlib.h>  // for exit

#define BUFFER_SIZE 1024

int main() {
    int src_fd, dest_fd;
    ssize_t n;
    char buffer[BUFFER_SIZE];

    // Open source file for reading
    src_fd = open("result.txt", O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        exit(1);
    }

    // Open/create destination file for writing (truncate if exists)
    dest_fd = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);
        exit(1);
    }

    // Read from source and write to destination
    while ((n = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest_fd, buffer, n) != n) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(1);
        }
    }

    if (n < 0) {
        perror("Error reading source file");
    }

    // Close files
    close(src_fd);
    close(dest_fd);

    printf("File copied successfully!\n");
    return 0;
}
