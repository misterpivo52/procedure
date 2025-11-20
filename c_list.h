#ifndef C_LIST_H
#define C_LIST_H
#include <stdio.h>

struct c_list;

struct c_list* create_list();
void destroy_list(struct c_list *list);
int append_list(struct c_list *list, const char *fmt, ...);

void print_list(const struct c_list *list, FILE *stream);
void print_element(const struct c_list *list, int index, FILE *stream);

int get_list_size(const struct c_list *list);
int get_list_int(const struct c_list *list, int index, int *value);
int get_list_float(const struct c_list *list, int index, float *value);
int get_list_string(const struct c_list *list, int index, const char **value);

#endif