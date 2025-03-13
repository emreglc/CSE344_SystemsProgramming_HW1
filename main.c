#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileManagerLib.h"
#include "helpers.h"

#define MAX_INPUT_LEN 256

int main() {
    char input[MAX_INPUT_LEN];
    char command[MAX_INPUT_LEN], arg1[MAX_INPUT_LEN], arg2[MAX_INPUT_LEN];

    printf("Welcome to File Manager! Type 'help' to see available commands.\n");
    while (1) {
        printf("fileManager> ");
        if (!fgets(input, MAX_INPUT_LEN, stdin)) {
            break;
        }

        input[strcspn(input, "\n")] = 0; // Remove newline character
        int args = sscanf(input, "%255s %255s %[^\n]", command, arg1, arg2);

        if (strcmp(command, "createDir") == 0 && args >= 2) {
            create_directory(arg1);
        } else if (strcmp(command, "createFile") == 0 && args >= 2) {
            create_file(arg1);
        } else if (strcmp(command, "listDir") == 0 && args >= 2) {
            list_directory(arg1);
        } else if (strcmp(command, "listFilesByExtension") == 0 && args >= 3) {
            list_files_by_extension(arg1, arg2);
        } else if (strcmp(command, "readFile") == 0 && args >= 2) {
            read_file(arg1);
        } else if (strcmp(command, "appendToFile") == 0 && args >= 3) {
            append_to_file(arg1, arg2);
        } else if (strcmp(command, "deleteFile") == 0 && args >= 2) {
            delete_file(arg1);
        } else if (strcmp(command, "deleteDir") == 0 && args >= 2) {
            delete_directory(arg1);
        } else if (strcmp(command, "showLogs") == 0) {
            show_logs();
        } else if (strcmp(command, "help") == 0) {
            show_help();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting File Manager...\n");
            break;
        } else {
            printf("Invalid command. Type 'help' for a list of commands.\n");
        }
    }
    return 0;
}