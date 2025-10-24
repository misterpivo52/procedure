#include <stdio.h>
#include "src/list.h"

int main(void) {
    void** mylist = create_list();

    int a = 5;
    float b = 3.14f;
    char* c = "hello";

    append_list(mylist, &a, int_type);
    append_list(mylist, &b, float_type);
    append_list(mylist, c, string_type);

    print_list(mylist);

    printf("\nCurrent size: %zu\n", get_list_size(mylist));
    printf("Capacity: %zu\n", get_list_capacity());

    return 0;
}