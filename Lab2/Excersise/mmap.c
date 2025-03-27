#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define FILEPATH "mmap_file.txt"
#define FILESIZE 4096

int main(void) {
    int fd;
    char *map;

    // Open (or create) the file for read/write.
    fd = open(FILEPATH, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Set the file size to FILESIZE bytes.
    if (ftruncate(fd, FILESIZE) == -1) {
        perror("ftruncate");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Map the file into memory with read and write permissions.
    map = (char *)mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }
    // The file descriptor is no longer needed after mmap.
    close(fd);

    // Create a child process.
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        munmap(map, FILESIZE);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process:
        // Wait briefly to let parent write first.
        sleep(1);
        printf("Child process reading message: \"%s\"\n", map);

        // Now the child writes a new message into the shared memory.
        snprintf(map, FILESIZE, "Hello from Child process!");
        printf("Child process updated message to: \"%s\"\n", map);
        exit(EXIT_SUCCESS);
    }
    else {
        // Parent process:
        // Write a message into the mapped memory.
        snprintf(map, FILESIZE, "Hello from Parent process!");
        printf("Parent process wrote message: \"%s\"\n", map);

        // Wait for the child to finish its update.
        wait(NULL);

        // Read back the updated message.
        printf("Parent process reading updated message: \"%s\"\n", map);

        // Unmap the memory region.
        if (munmap(map, FILESIZE) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
