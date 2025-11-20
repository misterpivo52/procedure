#include "c_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef enum { INT, FLOAT, STRING } list_data_type;

struct c_list_node {
    list_data_type type;
    union {
        int i;
        float f;
        char *s;
    } data;
};

struct c_list {
    struct c_list_node *nodes;
    int size;
    int capacity;
};

static int ensure_capacity(struct c_list *list, int required) {
    if (list->capacity >= required) return 0;
    int new_capacity = list->capacity * 2 > required ? list->capacity * 2 : required;
    struct c_list_node *new_nodes = realloc(list->nodes, new_capacity * sizeof(struct c_list_node));
    if (!new_nodes) return -1;
    list->nodes = new_nodes;
    list->capacity = new_capacity;
    return 0;
}

struct c_list* create_list() {
    struct c_list *list = malloc(sizeof(struct c_list));
    if (!list) return NULL;
    list->size = 0;
    list->capacity = 10;
    list->nodes = malloc(list->capacity * sizeof(struct c_list_node));
    if (!list->nodes) {
        free(list);
        return NULL;
    }
    return list;
}

void destroy_list(struct c_list *list) {
    if (!list) return;
    for (int i = 0; i < list->size; i++) {
        if (list->nodes[i].type == STRING) free(list->nodes[i].data.s);
    }
    free(list->nodes);
    free(list);
}

int append_list(struct c_list *list, const char *fmt, ...) {
    if (!list || !fmt) return -1;
    if (ensure_capacity(list, list->size + strlen(fmt)) != 0) return -1;

    va_list args;
    va_start(args, fmt);
    for (const char *p = fmt; *p; ++p) {
        struct c_list_node *node = &list->nodes[list->size];
        if (*p == 'd') {
            node->type = INT;
            node->data.i = va_arg(args, int);
        } else if (*p == 'f') {
            node->type = FLOAT;
            node->data.f = (float)va_arg(args, double);
        } else if (*p == 's') {
            char *s_val = va_arg(args, char*);
            node->type = STRING;
            node->data.s = malloc(strlen(s_val) + 1);
            if (node->data.s) strcpy(node->data.s, s_val);
        } else {
            continue;
        }
        list->size++;
    }
    va_end(args);
    return 0;
}

void print_list(const struct c_list *list, FILE *stream) {
    if (!list || !stream) return;
    for (int i = 0; i < list->size; i++) {
        switch (list->nodes[i].type) {
            case INT:    fprintf(stream, "%d ", list->nodes[i].data.i); break;
            case FLOAT:  fprintf(stream, "%f ", list->nodes[i].data.f); break;
            case STRING: fprintf(stream, "%s ", list->nodes[i].data.s); break;
        }
    }
    fprintf(stream, "\n");
}

void print_element(const struct c_list *list, int index, FILE *stream) {
    if (!list || !stream || index < 0 || index >= list->size) return;
    fprintf(stream, "Index %d = ", index);
    switch (list->nodes[index].type) {
        case INT:    fprintf(stream, "%d\n", list->nodes[index].data.i);   break;
        case FLOAT:  fprintf(stream, "%f\n", list->nodes[index].data.f);   break;
        case STRING: fprintf(stream, "%s\n", list->nodes[index].data.s); break;
    }
}

int get_list_size(const struct c_list *list) {
    return list ? list->size : 0;
}

static int get_value(const struct c_list *list, int index, void *value, list_data_type expected_type) {
    if (!list || index < 0 || index >= list->size || list->nodes[index].type != expected_type) {
        return 0;
    }
    if (expected_type == INT) {
        *(int*)value = list->nodes[index].data.i;
    } else if (expected_type == FLOAT) {
        *(float*)value = list->nodes[index].data.f;
    } else if (expected_type == STRING) {
        *(const char**)value = list->nodes[index].data.s;
    }
    return 1;
}

int get_list_int(const struct c_list *list, int index, int *value) {
    return get_value(list, index, value, INT);
}

int get_list_float(const struct c_list *list, int index, float *value) {
    return get_value(list, index, value, FLOAT);
}

int get_list_string(const struct c_list *list, int index, const char **value) {
    return get_value(list, index, value, STRING);
}