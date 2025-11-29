
#ifndef C_LIST_H
#define C_LIST_H

#include <stddef.h>

typedef enum {
    int_type,
    float_type,
    string_type
} list_data_type;

typedef struct c_list {
    void** data;
    list_data_type* types;
    size_t size;
    size_t capacity;

    int (*append)(struct c_list* list, void* item, list_data_type type);
    void* (*get)(const struct c_list* list, size_t index);
    int (*set)(struct c_list* list, size_t index, void* item, list_data_type type);
    int (*pop)(struct c_list* list);
    void (*print)(const struct c_list* list);
    void (*destroy)(struct c_list* list);
    struct c_list* (*copy)(const struct c_list* list);
    void (*clear)(struct c_list* list);
} c_list;

c_list* create_list(size_t initial_capacity);
c_list* create_list_from_file(const char *filename);
int dump_list_to_file(const c_list *list, const char *filename);

#endif