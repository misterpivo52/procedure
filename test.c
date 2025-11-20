#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include "c_list.h"

const char* TEMP_FILE = "test_output.tmp";

char* read_file_to_buffer(const char* filename) {
    FILE* f = fopen(filename, "rb");
    assert(f);
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buffer = malloc(len + 1);
    assert(buffer);
    fread(buffer, 1, len, f);
    buffer[len] = '\0';
    fclose(f);
    return buffer;
}

void test_create_destroy() {
    struct c_list *list = create_list();
    assert(list != NULL);
    assert(get_list_size(list) == 0);
    destroy_list(list);
    destroy_list(NULL);
}

void test_append_and_get() {
    struct c_list *list = create_list();
    int i_val;
    float f_val;
    const char* s_val;

    append_list(list, "d", 123);
    assert(get_list_size(list) == 1);
    assert(get_list_int(list, 0, &i_val) && i_val == 123);
    assert(!get_list_float(list, 0, &f_val));

    append_list(list, "f", 3.14f);
    assert(get_list_size(list) == 2);
    assert(get_list_float(list, 1, &f_val) && fabs(f_val - 3.14f) < 1e-6);

    append_list(list, "s", "hello");
    assert(get_list_size(list) == 3);
    assert(get_list_string(list, 2, &s_val) && strcmp(s_val, "hello") == 0);

    destroy_list(list);
}

void test_append_multiple() {
    struct c_list *list = create_list();
    int i_val;
    float f_val;
    const char* s_val;

    append_list(list, "dfs", 42, 1.23f, "world");
    assert(get_list_size(list) == 3);
    assert(get_list_int(list, 0, &i_val) && i_val == 42);
    assert(get_list_float(list, 1, &f_val) && fabs(f_val - 1.23f) < 1e-6);
    assert(get_list_string(list, 2, &s_val) && strcmp(s_val, "world") == 0);
    destroy_list(list);
}

void test_capacity_expansion() {
    struct c_list *list = create_list();
    for (int i = 0; i < 15; i++) {
        append_list(list, "d", i);
    }
    assert(get_list_size(list) == 15);
    int val;
    assert(get_list_int(list, 14, &val) && val == 14);
    destroy_list(list);
}

void test_print() {
    struct c_list *list = create_list();
    append_list(list, "dfs", 10, 2.5f, "test");

    FILE* f = fopen(TEMP_FILE, "wb");
    assert(f);
    print_list(list, f);
    fclose(f);

    char* buffer = read_file_to_buffer(TEMP_FILE);
    assert(strcmp(buffer, "10 2.500000 test \n") == 0);
    free(buffer);

    f = fopen(TEMP_FILE, "wb");
    assert(f);
    print_element(list, 1, f);
    fclose(f);

    buffer = read_file_to_buffer(TEMP_FILE);
    assert(strcmp(buffer, "Index 1 = 2.500000\n") == 0);
    free(buffer);
    
    remove(TEMP_FILE);
    destroy_list(list);
}

void test_edge_cases() {
    struct c_list *list = create_list();
    const char* s_val;
    
    append_list(list, "s", "");
    assert(get_list_size(list) == 1);
    assert(get_list_string(list, 0, &s_val) && strcmp(s_val, "") == 0);

    append_list(list, "z", 123);
    assert(get_list_size(list) == 1);

    assert(!get_list_int(list, 99, NULL));

    append_list(NULL, "d", 1);
    print_list(NULL, stdout);
    print_element(NULL, 0, stdout);
    
    destroy_list(list);
}

void test_empty_list_behavior() {
    struct c_list *list = create_list();
    assert(get_list_size(list) == 0);
    
    FILE* f = fopen(TEMP_FILE, "wb");
    assert(f);
    print_list(list, f);
    print_element(list, 0, f);
    fclose(f);

    char* buffer = read_file_to_buffer(TEMP_FILE);
    assert(strcmp(buffer, "\n") == 0);
    free(buffer);
    remove(TEMP_FILE);

    int i_val;
    assert(!get_list_int(list, 0, &i_val));

    destroy_list(list);
}

void test_stress_overflow() {
    struct c_list *list = create_list();
    for (int i = 0; i < 10000; i++) {
        append_list(list, "d", i);
    }
    assert(get_list_size(list) == 10000);
    
    int i_val;
    assert(get_list_int(list, 0, &i_val) && i_val == 0);
    assert(get_list_int(list, 9999, &i_val) && i_val == 9999);

    destroy_list(list);
}

void run_test(void (*test_func)(), const char* test_name) {
    printf("Running %s... ", test_name);
    test_func();
    printf("PASSED\n");
}

int main() {
    setlocale(LC_NUMERIC, "C");

    run_test(test_create_destroy, "test_create_destroy");
    run_test(test_append_and_get, "test_append_and_get");
    run_test(test_append_multiple, "test_append_multiple");
    run_test(test_capacity_expansion, "test_capacity_expansion");
    run_test(test_print, "test_print");
    run_test(test_edge_cases, "test_edge_cases");
    run_test(test_empty_list_behavior, "test_empty_list_behavior");
    run_test(test_stress_overflow, "test_stress_overflow");

    printf("\nAll tests passed successfully!\n");
    return 0;
}