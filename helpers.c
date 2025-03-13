#include "helpers.h"
#include <stdio.h>

void show_help() {
    printf("Usage: Enter a command followed by arguments if required.\n");
    printf("Commands:\n");
    printf("  createDir \"folderName\" - Create a new directory\n");
    printf("  createFile \"fileName\" - Create a new file\n");
    printf("  listDir \"folderName\" - List all files in a directory\n");
    printf("  listFilesByExtension \"folderName\" \".ext\" - List files with specific extension\n");
    printf("  readFile \"fileName\" - Read a file's content\n");
    printf("  appendToFile \"fileName\" \"new content\" - Append content to a file\n");
    printf("  deleteFile \"fileName\" - Delete a file\n");
    printf("  deleteDir \"folderName\" - Delete an empty directory\n");
    printf("  showLogs - Display operation logs\n");
    printf("  exit - Exit the program\n");
}

void show_logs() {
    printf("Operation logs:\n");
    // Implementation pending
}