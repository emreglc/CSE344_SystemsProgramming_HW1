#include "fileManagerLib.h"
#include "helpers.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void create_file(const char* file_name) {
    // Check if file already exists
    if (access(file_name, F_OK) != -1) {
        print("Error: File \"");
        print(file_name);
        print("\" already exists.\n");
        return;
    }

    int fd = open(file_name, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        print("Error creating file: ");
        print(strerror(errno));
        print("\n");
        return;
    }
    close(fd);
    print("File created successfully\n");

    char log_message[BUFFER_SIZE] = "File \"";
    strcat(log_message, file_name);
    strcat(log_message, "\" created successfully.");
    log_success(log_message);
}

void create_directory(const char* folder_name) {
    // Check if directory already exists
    struct stat dir_stat;
    if (stat(folder_name, &dir_stat) != -1 && S_ISDIR(dir_stat.st_mode)) {
        print("Error: Directory \"");
        print(folder_name);
        print("\" already exists.\n");
        return;
    }

    if (mkdir(folder_name, 0755) == -1) {
        print("Error creating directory: ");
        print(strerror(errno));
        print("\n");
        return;
    }
    print("Directory created successfully\n");

    char log_message[BUFFER_SIZE] = "Directory \"";
    strcat(log_message, folder_name);
    strcat(log_message, "\" created successfully.");
    log_success(log_message);
}

void list_directory(const char* folder_name) {
    struct stat dir_stat;

    // Check if the directory exists
    if (stat(folder_name, &dir_stat) == -1 || !S_ISDIR(dir_stat.st_mode)) {
        print("Error: Directory \"");
        print(folder_name);
        print("\" not found.\n");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        print("Error: Failed to create process.\n");
        return;
    }

    if (pid == 0) {
        // Child process: Execute "ls -l folder_name"
        execlp("ls", "ls", "-l", folder_name, (char*)NULL);

        // If execlp fails, print an error
        print("Error: Failed to execute ls command.\n");
        exit(EXIT_FAILURE);
    } else {
        // Parent process: Wait for child to complete
        wait(NULL);
        char log_message[BUFFER_SIZE] = "Listed directory \"";
        strcat(log_message, folder_name);
        strcat(log_message, "\" successfully.");
        log_success(log_message);
    }
}

void list_files_by_extension(const char* folder_name, const char* extension) {
    struct stat dir_stat;

    // Check if the directory exists
    if (stat(folder_name, &dir_stat) == -1 || !S_ISDIR(dir_stat.st_mode)) {
        print("Error: Directory \"");
        print(folder_name);
        print("\" not found.\n");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        print("Error: Failed to create process.\n");
        return;
    }

    if (pid == 0) {
        // Child process: Execute "find folder_name -type f -name '*.extension'"
        
        // Construct the correct pattern with wildcard
        char pattern[BUFFER_SIZE] = "*";
        strcat(pattern, extension);  // Example: "*.txt"

        execlp("find", "find", folder_name, "-type", "f", "-name", pattern, (char*)NULL);

        // If execlp fails
        print("Error: Failed to execute find command.\n");
        exit(EXIT_FAILURE);
    } else {
        // Parent process: Wait for child to complete
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            char log_message[BUFFER_SIZE] = "Listed files with extension \"";
            strcat(log_message, extension);
            strcat(log_message, "\" in directory \"");
            strcat(log_message, folder_name);
            strcat(log_message, "\" successfully.");
            log_success(log_message);
        } else {
            print("Error: Failed to list files.\n");
        }
    }
}

void read_file(const char* file_name) {
    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        print("Error: Unable to open file for reading.\n");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    print("\n");

    if (bytes_read == -1) {
        print("Error: Unable to read file.\n");
    }

    close(fd);
}

void append_to_file(const char* file_name, const char* content) {
    int fd = open(file_name, O_WRONLY | O_APPEND);
    if (fd == -1) {
        print("Error: Unable to open file for appending.\n");
        return;
    }

    size_t len = strlen(content);
    if (write(fd, content, len) != len) {
        print("Error: Unable to write to file.\n");
    }

    // Append a newline for better formatting
    write(fd, "\n", 1);

    close(fd);
}

void delete_file(const char *file_name) {
    pid_t pid = fork();

    if (pid == -1) {
        print("Error: Failed to create process.\n");
        return;
    }

    if (pid == 0) {  // Child process
        // Check if file exists
        if (access(file_name, F_OK) == -1) {
            print("Error: File \"");
            print(file_name);
            print("\" not found.\n");
            _exit(EXIT_FAILURE);
        }

        // Attempt to delete file
        if (unlink(file_name) == -1) {
            print("Error: Unable to delete file \"");
            print(file_name);
            print("\" - ");
            print(strerror(errno));
            print("\n");
            _exit(EXIT_FAILURE);
        }

        print("File \"");
        print(file_name);
        print("\" deleted successfully.\n");

        char log_message[BUFFER_SIZE] = "File \"";
        strcat(log_message, file_name);
        strcat(log_message, "\" deleted successfully.");
        log_success(log_message);

        _exit(EXIT_SUCCESS);
    } else {  // Parent process
        waitpid(pid, NULL, 0);
    }
}

void delete_directory(const char *dir_name) {
    pid_t pid = fork();

    if (pid == -1) {
        print("Error: Failed to create process.\n");
        return;
    }

    if (pid == 0) {  // Child process
        struct stat dir_stat;

        // Check if directory exists
        if (stat(dir_name, &dir_stat) == -1 || !S_ISDIR(dir_stat.st_mode)) {
            print("Error: Directory \"");
            print(dir_name);
            print("\" not found.\n");
            _exit(EXIT_FAILURE);
        }

        // Attempt to remove directory
        if (rmdir(dir_name) == -1) {
            print("Error: Unable to delete directory \"");
            print(dir_name);
            print("\" - ");
            print(strerror(errno));
            print("\n");
            _exit(EXIT_FAILURE);
        }

        print("Directory \"");
        print(dir_name);
        print("\" deleted successfully.\n");

        char log_message[BUFFER_SIZE] = "Directory \"";
        strcat(log_message, dir_name);
        strcat(log_message, "\" deleted successfully.");
        log_success(log_message);

        _exit(EXIT_SUCCESS);
    } else {  // Parent process
        waitpid(pid, NULL, 0);
    }
}