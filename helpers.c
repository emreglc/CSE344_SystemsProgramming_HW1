#include "helpers.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define LOG_FILE "log.txt"

void print(const char* message) {
    write(STDOUT_FILENO, message, strlen(message));
}

void print_usage() {
    print("Usage: fileManager <command> [arguments]\n");
    print("Commands:\n");
    print("  createDir \"folderName\" - Create a new directory\n");
    print("  createFile \"fileName\" - Create a new file\n");
    print("  listDir \"folderName\" - List all files in a directory\n");
    print("  listFilesByExtension \"folderName\" \".ext\" - List files with specific extension\n");
    print("  readFile \"fileName\" - Read a file's content\n");
    print("  appendToFile \"fileName\" \"new content\" - Append content to a file\n");
    print("  deleteFile \"fileName\" - Delete a file\n");
    print("  deleteDir \"folderName\" - Delete an empty directory\n");
    print("  showLogs - Display operation logs\n");
}

// Helper function to convert an integer (0-99) to a 2-character string
void int_to_str2(int num, char *buf) {
    buf[0] = '0' + (num / 10);
    buf[1] = '0' + (num % 10);
}

// Get formatted timestamp using system calls
void get_timestamp(char *buffer) {
    time_t now = time(NULL);
    struct tm t;
    gmtime_r(&now, &t);

    char temp[32]; // Temporary buffer for timestamp
    int index = 0;

    // Year
    int year = t.tm_year + 1900;
    temp[index++] = '0' + ((year / 1000) % 10);
    temp[index++] = '0' + ((year / 100) % 10);
    temp[index++] = '0' + ((year / 10) % 10);
    temp[index++] = '0' + (year % 10);
    temp[index++] = '-';

    // Month
    int_to_str2(t.tm_mon + 1, &temp[index]);
    index += 2;
    temp[index++] = '-';

    // Day
    int_to_str2(t.tm_mday, &temp[index]);
    index += 2;
    temp[index++] = ' ';

    // Hour
    int_to_str2(t.tm_hour, &temp[index]);
    index += 2;
    temp[index++] = ':';

    // Minute
    int_to_str2(t.tm_min, &temp[index]);
    index += 2;
    temp[index++] = ':';

    // Second
    int_to_str2(t.tm_sec, &temp[index]);
    index += 2;

    temp[index++] = ']';
    temp[index++] = ' ';
    temp[index] = '\0';

    // Copy to the provided buffer
    strcpy(buffer, "[");
    strcat(buffer, temp);
}

void log_success(const char *message) {
    int fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        write(STDOUT_FILENO, "Error: Unable to open log file.\n", 32);
        return;
    }

    char timestamp[32];
    get_timestamp(timestamp);

    write(fd, timestamp, strlen(timestamp));
    write(fd, message, strlen(message));
    write(fd, "\n", 1);

    close(fd);
}

// Function to show logs using fork()
void show_logs() {
    pid_t pid = fork();

    if (pid == -1) {
        write(STDOUT_FILENO, "Error: Failed to create process.\n", 32);
        return;
    }

    if (pid == 0) { // Child process
        int fd = open(LOG_FILE, O_RDONLY);
        if (fd == -1) {
            write(STDOUT_FILENO, "Error: No logs available.\n", 26);
            _exit(EXIT_FAILURE);
        }

        char buffer[256];
        ssize_t bytes_read;
        while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        close(fd);
        _exit(EXIT_SUCCESS);
    } else { // Parent process
        waitpid(pid, NULL, 0);
    }
}