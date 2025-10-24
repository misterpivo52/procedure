#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef enum {
    int_type,
    float_type,
    string_type
} list_data_type;

void** create_list(void);
int append_list(void** list, void* item, list_data_type type);
void print_list(void** list);
size_t get_list_size(void** list);
size_t get_list_capacity(void);

#endif