#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef enum {
    int_type,
    float_type,
    string_type
} list_data_type;

typedef struct {
    void** data;
    list_data_type* types;
    size_t size;
    size_t capacity;
} List;

List* create_list(void);
int append_list(List* list, void* item, list_data_type type);
void print_list(List* list);
size_t get_list_size(List* list);
size_t get_list_capacity(List* list);
int pop_list(List* list);
void free_list(List* list);

#endif