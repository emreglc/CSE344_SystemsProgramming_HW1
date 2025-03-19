#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
    print("  exit - Exit the program\n");
}

void show_logs() {
    print("Operation logs:\n");
    // Implementation pending
}