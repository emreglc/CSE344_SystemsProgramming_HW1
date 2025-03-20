#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "fileManagerLib.h"
#include "helpers.h"

// Function to trim surrounding quotes from a string
void trim_quotes(char* str) {
    size_t len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print("Usage: fileManager <command> [arguments]\n");
        print("Commands:\n");
        print("  createDir \"folderName\" - Create a new directory\n");
        print("  createFile \"fileName\" - Create a new file\n");
        print("  listDir \"folderName\" - List all files in a directory\n");
        print("  listFilesByExtension \"folderName\" \".txt\" - List files with specific extension\n");
        print("  readFile \"fileName\" - Read a file's content\n");
        print("  appendToFile \"fileName\" \"new content\" - Append content to a file\n");
        print("  deleteFile \"fileName\" - Delete a file\n");
        print("  deleteDir \"folderName\" - Delete an empty directory\n");
        print("  showLogs - Display operation logs\n");
        return 1;
    }

    char command[256];
    strncpy(command, argv[1], sizeof(command) - 1);
    command[sizeof(command) - 1] = '\0';

    if (argc >= 3) trim_quotes(argv[2]);
    if (argc >= 4) trim_quotes(argv[3]);

    if (strcmp(command, "createDir") == 0 && argc >= 3) {
        create_directory(argv[2]);
    }
    else if (strcmp(command, "createFile") == 0 && argc >= 3) {
        create_file(argv[2]);
    }
    else if (strcmp(command, "listDir") == 0 && argc >= 3) {
        list_directory(argv[2]);
    }
    else if (strcmp(command, "listFilesByExtension") == 0 && argc >= 4) {
        list_files_by_extension(argv[2], argv[3]);
    }
    else if (strcmp(command, "readFile") == 0 && argc >= 3) {
        read_file(argv[2]);
    }
    else if (strcmp(command, "appendToFile") == 0 && argc >= 4) {
        append_to_file(argv[2], argv[3]);
    }
    else if (strcmp(command, "deleteFile") == 0 && argc >= 3) {
        delete_file(argv[2]);
    }
    else if (strcmp(command, "deleteDir") == 0 && argc >= 3) {
        delete_directory(argv[2]);
    }
    else if (strcmp(command, "showLogs") == 0) {
        show_logs();
    }
    else {
        print("Invalid command. Type 'fileManager' for a list of commands.\n");
    }

    return 0;
}
