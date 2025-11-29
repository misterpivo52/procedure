
#include "c_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2

static int append_impl(c_list* list, void* item, list_data_type type);
static void* get_impl(const c_list* list, size_t index);
static int set_impl(c_list* list, size_t index, void* item, list_data_type type);
static int pop_impl(c_list* list);
static void print_impl(const c_list* list);
static void destroy_impl(c_list* list);
static c_list* copy_impl(const c_list* list);
static void clear_impl(c_list* list);

static void* copy_data(void* item, list_data_type type) {
    void* stored_item = NULL;

    if (type == int_type) {
        stored_item = malloc(sizeof(int));
        if (stored_item) {
            *(int*)stored_item = *(int*)item;
        }
    } else if (type == float_type) {
        stored_item = malloc(sizeof(float));
        if (stored_item) {
            *(float*)stored_item = *(float*)item;
        }
    } else if (type == string_type) {
        size_t len = strlen((char*)item);
        stored_item = malloc(len + 1);
        if (stored_item) {
            strcpy((char*)stored_item, (char*)item);
        }
    }

    return stored_item;
}

static int append_impl(c_list* list, void* item, list_data_type type) {
    if (list == NULL) {
        return -1;
    }

    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        void** new_data = (void**)realloc(list->data, new_capacity * sizeof(void*));
        list_data_type* new_types = (list_data_type*)realloc(list->types, new_capacity * sizeof(list_data_type));

        if (new_data == NULL || new_types == NULL) {
            return -1;
        }

        list->data = new_data;
        list->types = new_types;
        list->capacity = new_capacity;
    }

    void* stored_item = copy_data(item, type);
    if (stored_item == NULL) {
        return -1;
    }

    list->data[list->size] = stored_item;
    list->types[list->size] = type;
    list->size++;

    return 0;
}

static void* get_impl(const c_list* list, size_t index) {
    if (list == NULL || index >= list->size) {
        return NULL;
    }
    return list->data[index];
}

static int set_impl(c_list* list, size_t index, void* item, list_data_type type) {
    if (list == NULL || index >= list->size) {
        return -1;
    }

    free(list->data[index]);

    void* stored_item = copy_data(item, type);
    if (stored_item == NULL) {
        return -1;
    }

    list->data[index] = stored_item;
    list->types[index] = type;

    return 0;
}

static int pop_impl(c_list* list) {
    if (list == NULL || list->size == 0) {
        return -1;
    }

    free(list->data[list->size - 1]);
    list->size--;

    if (list->size > 0 && list->size <= list->capacity / 4 && list->capacity > INITIAL_CAPACITY) {
        size_t new_capacity = list->capacity / 2;
        void** new_data = (void**)realloc(list->data, new_capacity * sizeof(void*));
        list_data_type* new_types = (list_data_type*)realloc(list->types, new_capacity * sizeof(list_data_type));

        if (new_data != NULL && new_types != NULL) {
            list->data = new_data;
            list->types = new_types;
            list->capacity = new_capacity;
        }
    }

    return 0;
}

static void print_impl(const c_list* list) {
    if (list == NULL) {
        return;
    }

    printf("[");
    for (size_t i = 0; i < list->size; i++) {
        if (list->types[i] == int_type) {
            printf("%d", *(int*)list->data[i]);
        } else if (list->types[i] == float_type) {
            printf("%f", *(float*)list->data[i]);
        } else if (list->types[i] == string_type) {
            printf("\"%s\"", (char*)list->data[i]);
        }
        if (i < list->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

static void destroy_impl(c_list* list) {
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < list->size; i++) {
        free(list->data[i]);
    }

    free(list->data);
    free(list->types);
    free(list);
}

static c_list* copy_impl(const c_list* list) {
    if (list == NULL) {
        return NULL;
    }

    c_list* new_list = create_list(list->capacity);
    if (new_list == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < list->size; i++) {
        if (new_list->append(new_list, list->data[i], list->types[i]) != 0) {
            new_list->destroy(new_list);
            return NULL;
        }
    }

    return new_list;
}

static void clear_impl(c_list* list) {
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < list->size; i++) {
        free(list->data[i]);
    }

    list->size = 0;
}

c_list* create_list(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = INITIAL_CAPACITY;
    }

    c_list* list = (c_list*)malloc(sizeof(c_list));
    if (list == NULL) {
        return NULL;
    }

    list->data = (void**)malloc(initial_capacity * sizeof(void*));
    list->types = (list_data_type*)malloc(initial_capacity * sizeof(list_data_type));

    if (list->data == NULL || list->types == NULL) {
        free(list->data);
        free(list->types);
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = initial_capacity;

    list->append = append_impl;
    list->get = get_impl;
    list->set = set_impl;
    list->pop = pop_impl;
    list->print = print_impl;
    list->destroy = destroy_impl;
    list->copy = copy_impl;
    list->clear = clear_impl;

    return list;
}

c_list* create_list_from_file(const char *filename) {
    if (filename == NULL) {
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    c_list* list = create_list(INITIAL_CAPACITY);
    if (list == NULL) {
        fclose(file);
        return NULL;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char type_str[20];
        char value[256];

        if (sscanf(line, "%s %[^\n]", type_str, value) == 2) {
            if (strcmp(type_str, "int") == 0) {
                int val = atoi(value);
                list->append(list, &val, int_type);
            } else if (strcmp(type_str, "float") == 0) {
                float val = atof(value);
                list->append(list, &val, float_type);
            } else if (strcmp(type_str, "string") == 0) {
                list->append(list, value, string_type);
            }
        }
    }

    fclose(file);
    return list;
}

int dump_list_to_file(const c_list *list, const char *filename) {
    if (list == NULL || filename == NULL) {
        return -1;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }

    for (size_t i = 0; i < list->size; i++) {
        if (list->types[i] == int_type) {
            fprintf(file, "int %d\n", *(int*)list->data[i]);
        } else if (list->types[i] == float_type) {
            fprintf(file, "float %f\n", *(float*)list->data[i]);
        } else if (list->types[i] == string_type) {
            fprintf(file, "string %s\n", (char*)list->data[i]);
        }
    }

    fclose(file);
    return 0;
}