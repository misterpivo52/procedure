#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
    List* listA = create_list();
    List* listB = create_list();

    assert(listA != NULL);
    assert(listB != NULL);

    int val1 = 5;
    float val2 = 3.14f;

    append_list(listA, &val1, int_type);
    append_list(listA, &val2, float_type);
    append_list(listA, "hello", string_type);

    assert(get_list_size(listA) == 3);

    int val3 = 10;
    append_list(listB, &val3, int_type);
    append_list(listB, "world", string_type);

    assert(get_list_size(listB) == 2);

    printf("List A:\n");
    print_list(listA);
    printf("A size: %zu, capacity: %zu\n", get_list_size(listA), get_list_capacity(listA));

    printf("\nList B:\n");
    print_list(listB);
    printf("B size: %zu, capacity: %zu\n", get_list_size(listB), get_list_capacity(listB));

    printf("\nPopped last element from List A\n");
    pop_list(listA);

    printf("List A after pop:\n");
    print_list(listA);
    printf("A size: %zu\n", get_list_size(listA));

    assert(get_list_size(listA) == 2);

    free_list(listA);
    free_list(listB);

    printf("\nAll tests passed\n");
    return 0;
}