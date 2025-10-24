#include <stdio.h>
#include <assert.h>
#include "../src/list.h"

void test_create_list() {
    void** list = create_list();
    assert(list != NULL);
    assert(get_list_size(list) == 0);
    printf("test_create_list passed\n");
}

void test_append_list() {
    void** list = create_list();
    int x = 10;
    int result = append_list(list, &x, int_type);
    assert(result == 0);
    assert(get_list_size(list) == 1);
    printf("test_append_list passed\n");
}

void test_get_capacity() {
    size_t capacity = get_list_capacity();
    assert(capacity == 100);
    printf("test_get_capacity passed\n");
}

void test_get_size() {
    void** list = create_list();
    int a = 1, b = 2;
    append_list(list, &a, int_type);
    append_list(list, &b, int_type);
    assert(get_list_size(list) == 2);
    printf("test_get_size passed\n");
}

void test_mixed_types() {
    void** list = create_list();
    int x = 42;
    float y = 3.14f;
    char* z = "test";
    append_list(list, &x, int_type);
    append_list(list, &y, float_type);
    append_list(list, z, string_type);
    assert(get_list_size(list) == 3);
    printf("test_mixed_types passed\n");
}

int main() {
    test_create_list();
    test_append_list();
    test_get_capacity();
    test_get_size();
    test_mixed_types();
    printf("\nAll tests passed!\n");
    return 0;
}