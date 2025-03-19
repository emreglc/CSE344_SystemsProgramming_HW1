#include "fileManagerLib.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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
    // Implementation pending
}

void append_to_file(const char *file_name, const char *content) {
    // Implementation pending
}

void delete_file(const char *file_name) {
    // Implementation pending
}

void delete_directory(const char *folder_name) {
    // Implementation pending
}