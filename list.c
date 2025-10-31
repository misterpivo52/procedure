#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 2

List* create_list(void) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    (*list).data = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
    (*list).types = (list_data_type*)malloc(INITIAL_CAPACITY * sizeof(list_data_type));

    if ((*list).data == NULL || (*list).types == NULL) {
        free((*list).data);
        free((*list).types);
        free(list);
        return NULL;
    }

    (*list).size = 0;
    (*list).capacity = INITIAL_CAPACITY;
    return list;
}

int append_list(List* list, void* item, list_data_type type) {
    if (list == NULL) {
        return -1;
    }

    if ((*list).size >= (*list).capacity) {
        size_t new_capacity = (*list).capacity * 2;
        void** new_data = (void**)realloc((*list).data, new_capacity * sizeof(void*));
        list_data_type* new_types = (list_data_type*)realloc((*list).types, new_capacity * sizeof(list_data_type));

        if (new_data == NULL || new_types == NULL) {
            return -1;
        }

        (*list).data = new_data;
        (*list).types = new_types;
        (*list).capacity = new_capacity;
    }

    (*list).data[(*list).size] = item;
    (*list).types[(*list).size] = type;
    (*list).size++;
    return 0;
}

int pop_list(List* list) {
    if (list == NULL || (*list).size == 0) {
        return -1;
    }

    (*list).size--;

    if ((*list).size > 0 && (*list).size <= (*list).capacity / 4 && (*list).capacity > INITIAL_CAPACITY) {
        size_t new_capacity = (*list).capacity / 2;
        void** new_data = (void**)realloc((*list).data, new_capacity * sizeof(void*));
        list_data_type* new_types = (list_data_type*)realloc((*list).types, new_capacity * sizeof(list_data_type));

        if (new_data != NULL && new_types != NULL) {
            (*list).data = new_data;
            (*list).types = new_types;
            (*list).capacity = new_capacity;
        }
    }

    return 0;
}

void print_list(List* list) {
    if (list == NULL) {
        return;
    }

    printf("List size = %zu\n", (*list).size);
    for (size_t i = 0; i < (*list).size; i++) {
        if ((*list).types[i] == int_type) {
            printf("%d ", *(int*)(*list).data[i]);
        } else if ((*list).types[i] == float_type) {
            printf("%f ", *(float*)(*list).data[i]);
        } else if ((*list).types[i] == string_type) {
            printf("%s ", (char*)(*list).data[i]);
        }
    }
    printf("\n");
}

size_t get_list_size(List* list) {
    if (list == NULL) {
        return 0;
    }
    return (*list).size;
}

size_t get_list_capacity(List* list) {
    if (list == NULL) {
        return 0;
    }
    return (*list).capacity;
}

void free_list(List* list) {
    if (list == NULL) {
        return;
    }
    free((*list).data);
    free((*list).types);
    free(list);
}