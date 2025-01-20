#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <fcntl.h>

// Function to get the current system time as a string
void get_current_time(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// Function to write username, password, and system info to a file
void create_user_profile() {
    char username[50] = {0};
    char password[50] = {0};
    char buffer[1024] = {0}; // Buffer to construct the content
    char time_buffer[100] = {0};
    struct utsname sys_info;

    // Get username
    write(STDOUT_FILENO, "Enter username: ", 16);
    read(STDIN_FILENO, username, sizeof(username));
    username[strcspn(username, "\n")] = '\0'; // Remove newline

    // Get password
    write(STDOUT_FILENO, "Enter password: ", 16);
    read(STDIN_FILENO, password, sizeof(password));
    password[strcspn(password, "\n")] = '\0'; // Remove newline

    // Get system information
    uname(&sys_info);

    // Get current time
    get_current_time(time_buffer, sizeof(time_buffer));

    // Construct the profile content
    snprintf(buffer, sizeof(buffer),
             "Username: %s\nPassword: %s\nSystem: %s\nNode Name: %s\nRelease: %s\nVersion: %s\nMachine: %s\nTimestamp: %s\n",
             username, password, sys_info.sysname, sys_info.nodename, sys_info.release, sys_info.version,
             sys_info.machine, time_buffer);

    // Open the file for writing
    int fd = open("profile.config.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // Write the content to the file
    if (write(fd, buffer, strlen(buffer)) < 0) {
        perror("Error writing to file");
        close(fd);
        return;
    }

    close(fd); // Close the file
    write(STDOUT_FILENO, "User profile saved in 'profile.config.txt'.\n", 44);
}

// Main function
int main() {
    create_user_profile();
    return 0;
}
