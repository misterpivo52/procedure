#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    List* list = create_list();
    if (list == NULL) {
        printf("Error creating list\n");
        return 1;
    }

    char command[100];
    printf("List Operations Program\n");
    printf("Commands: append_int <value>, append_float <value>, append_string <text>, print, size, capacity, pop, quit\n\n");

    while (1) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "quit") == 0) {
            break;
        } else if (strcmp(command, "print") == 0) {
            print_list(list);
        } else if (strcmp(command, "size") == 0) {
            printf("Size: %zu\n", get_list_size(list));
        } else if (strcmp(command, "capacity") == 0) {
            printf("Capacity: %zu\n", get_list_capacity(list));
        } else if (strcmp(command, "pop") == 0) {
            if (pop_list(list) == 0) {
                printf("Popped last element\n");
            } else {
                printf("Cannot pop from empty list\n");
            }
        } else if (strncmp(command, "append_int ", 11) == 0) {
            int* val = (int*)malloc(sizeof(int));
            *val = atoi(command + 11);
            append_list(list, val, int_type);
            printf("Added int: %d\n", *val);
        } else if (strncmp(command, "append_float ", 13) == 0) {
            float* val = (float*)malloc(sizeof(float));
            *val = atof(command + 13);
            append_list(list, val, float_type);
            printf("Added float: %f\n", *val);
        } else if (strncmp(command, "append_string ", 14) == 0) {
            char* str = strdup(command + 14);
            append_list(list, str, string_type);
            printf("Added string: %s\n", str);
        } else {
            printf("Unknown command\n");
        }
    }

    for (size_t i = 0; i < get_list_size(list); i++) {
        if (list->types[i] == int_type || list->types[i] == float_type) {
            free(list->data[i]);
        } else if (list->types[i] == string_type) {
            free(list->data[i]);
        }
    }

    free_list(list);
    return 0;
}