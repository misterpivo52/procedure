#include "list.h"
#include <stdio.h>

#define MAX_CAPACITY 100

static void* global_list[MAX_CAPACITY];
static list_data_type global_types[MAX_CAPACITY];
static size_t global_size = 0;

void** create_list(void) {
    global_size = 0;
    return global_list;
}

int append_list(void** list, void* item, list_data_type type) {
    if (global_size >= MAX_CAPACITY) {
        return -1;
    }
    global_list[global_size] = item;
    global_types[global_size] = type;
    global_size++;
    return 0;
}

void print_list(void** list) {
    printf("List size = %zu\n", global_size);
    for (size_t i = 0; i < global_size; i++) {
        if (global_types[i] == int_type) {
            printf("%d ", *(int*)global_list[i]);
        } else if (global_types[i] == float_type) {
            printf("%f ", *(float*)global_list[i]);
        } else if (global_types[i] == string_type) {
            printf("%s ", (char*)global_list[i]);
        }
    }
    printf("\n");
}

size_t get_list_size(void** list) {
    return global_size;
}

size_t get_list_capacity(void) {
    return MAX_CAPACITY;
}