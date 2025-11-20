#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_list.h"

void print_help() {
    printf("Commands:\n"
           "  append int <value>    - Append an integer\n"
           "  append float <value>  - Append a float\n"
           "  append string <value> - Append a string\n"
           "  get <index>           - Get element by index\n"
           "  print                 - Print the entire list\n"
           "  size                  - Get the size of the list\n"
           "  destroy               - Destroy and recreate the list\n"
           "  help                  - Show this help message\n"
           "  quit                  - Exit the program\n");
}

int main() {
    char line[256], command[32];
    struct c_list *list = create_list();
    if (!list) return 1;

    printf("Interactive c_list program. Type 'help' for commands.\n");

    while (printf("> ") && fgets(line, sizeof(line), stdin)) {
        sscanf(line, "%s", command);

        if (strcmp(command, "quit") == 0) break;
        if (strcmp(command, "help") == 0) print_help();
        else if (strcmp(command, "print") == 0) print_list(list, stdout);
        else if (strcmp(command, "size") == 0) printf("Size: %d\n", get_list_size(list));
        else if (strcmp(command, "destroy") == 0) {
            destroy_list(list);
            list = create_list();
            printf("List destroyed and recreated.\n");
        } else if (strcmp(command, "get") == 0) {
            int index;
            if (sscanf(line, "%*s %d", &index) == 1) print_element(list, index, stdout);
            else printf("Invalid 'get' command.\n");
        } else if (strcmp(command, "append") == 0) {
            char type[16];
            if (sscanf(line, "%*s %s", type) == 1) {
                if (strcmp(type, "int") == 0) {
                    int val;
                    if (sscanf(line, "%*s %*s %d", &val) == 1) append_list(list, "d", val);
                } else if (strcmp(type, "float") == 0) {
                    float val;
                    if (sscanf(line, "%*s %*s %f", &val) == 1) append_list(list, "f", val);
                } else if (strcmp(type, "string") == 0) {
                    char *val_ptr = strstr(line, "string") + 6;
                    while (*val_ptr == ' ') val_ptr++;
                    char *end = strrchr(val_ptr, '\n');
                    if (end) *end = '\0';
                    append_list(list, "s", val_ptr);
                }
            }
        } else printf("Unknown command: %s\n", command);
    }

    destroy_list(list);
    printf("Program finished.\n");
    return 0;
}