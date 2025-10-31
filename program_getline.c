#include "getline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char filename[256];
    char command[100];

    printf("Getline Operations Program\n");
    printf("Commands: read <filename>, stdin, quit\n\n");

    while (1) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "quit") == 0) {
            break;
        } else if (strcmp(command, "stdin") == 0) {
            printf("Enter lines (Ctrl+D to stop):\n");
            int line_num = 1;
            while ((nread = getline(&line, &len, stdin)) != -1) {
                printf("Line %d (%zd chars): %s", line_num, nread, line);
                line_num++;
            }
            clearerr(stdin);
        } else if (strncmp(command, "read ", 5) == 0) {
            strncpy(filename, command + 5, sizeof(filename) - 1);
            filename[sizeof(filename) - 1] = '\0';

            FILE *fp = fopen(filename, "r");
            if (fp == NULL) {
                printf("Cannot open file: %s\n", filename);
                continue;
            }

            printf("Reading from %s:\n", filename);
            int line_num = 1;
            while ((nread = getline(&line, &len, fp)) != -1) {
                printf("Line %d (%zd chars): %s", line_num, nread, line);
                line_num++;
            }

            fclose(fp);
            printf("Finished reading file\n");
        } else {
            printf("Unknown command\n");
        }
    }

    free(line);
    return 0;
}