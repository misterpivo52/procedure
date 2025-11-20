#include "c_list.h"

int main() {
    struct c_list *lst = create_list();
    append_list(lst, "d", 42);
    append_list(lst, "f", 3.14f);
    append_list(lst, "s", "hello");
    
    print_list(lst, stdout);
    
    print_element(lst, 0, stdout);
    print_element(lst, 1, stdout);
    print_element(lst, 2, stdout);
    
    destroy_list(lst);
    return 0;
}