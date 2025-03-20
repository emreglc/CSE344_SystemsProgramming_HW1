#include "fileManagerLib.h"
#include "helpers.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void create_file(const char *file_name) {
    int fd = open(file_name, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        print("Error creating file: ");
        print(strerror(errno));
        print("\n");
        return;
    }
    close(fd);
    print("File created successfully\n");
}

void create_directory(const char *folder_name) {
    if (mkdir(folder_name, 0755) == -1) {
        print("Error creating directory: ");
        print(strerror(errno));
        print("\n");
        return;
    }
    print("Directory created successfully\n");
}

void list_directory(const char *folder_name) {
    // Implementation pending
}

void list_files_by_extension(const char *folder_name, const char *extension) {
    // Implementation pending
}

void read_file(const char *file_name) {
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

void append_to_file(const char *file_name, const char *content) {
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
    // Implementation pending
}

void delete_directory(const char *folder_name) {
    // Implementation pending
}