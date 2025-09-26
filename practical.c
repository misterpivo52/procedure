#include <stdio.h>

enum Permission {
    READ    = 1 << 2,
    WRITE   = 1 << 1,
    EXECUTE = 1 << 0
};

void print_permissions(int octal_digit) {
    if (octal_digit & READ) {
        printf("r");
    } else {
        printf("-");
    }
    
    if (octal_digit & WRITE) {
        printf("w");
    } else {
        printf("-");
    }
    
    if (octal_digit & EXECUTE) {
        printf("x");
    } else {
        printf("-");
    }
}

int main() {
    int perm_num;
    printf("Enter permission (e.g., 754): ");
    if (scanf("%d", &perm_num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (perm_num < 0 || perm_num > 777) {
        printf("Permission must be between 0 and 777\n");
        return 1;
    }
    
    int owner = (perm_num / 100) % 10;
    int group = (perm_num / 10) % 10;
    int others = perm_num % 10;
    
    if (owner > 7 || group > 7 || others > 7) {
        printf("Each digit must be between 0 and 7\n");
        return 1;
    }
    
    printf("Permissions: ");
    
    print_permissions(owner);
    print_permissions(group);
    print_permissions(others);
    
    printf("\n");
    
    return 0;
}
