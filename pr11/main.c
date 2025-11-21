#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int item;
    struct Node *next;
} Node;

Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;
    
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;
}

Node *partition_list(Node *head, int x) {
    Node *before_head = NULL;
    Node *before_tail = NULL;
    Node *after_head = NULL;
    Node *after_tail = NULL;
    
    Node *curr = head;
    
    while (curr != NULL) {
        if (curr->item < x) {
            if (before_head == NULL) {
                before_head = curr;
                before_tail = curr;
            } else {
                before_tail->next = curr;
                before_tail = curr;
            }
        } else {
            if (after_head == NULL) {
                after_head = curr;
                after_tail = curr;
            } else {
                after_tail->next = curr;
                after_tail = curr;
            }
        }
        curr = curr->next;
    }
    
    if (before_head == NULL) {
        return after_head;
    }
    
    if (after_head != NULL) {
        before_tail->next = after_head;
        after_tail->next = NULL;
    } else {
        before_tail->next = NULL;
    }
    
    return before_head;
}

Node *create_node(int item) {
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newnode->item = item;
    newnode->next = NULL;
    return newnode;
}

Node *insert_back(Node *head, int item) {
    Node *newnode = create_node(item);
    if (newnode == NULL) return head;
    
    if (head == NULL) {
        return newnode;
    }
    
    Node *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newnode;
    return head;
}

void print_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%d", curr->item);
        if (curr->next != NULL) {
            printf(" -> ");
        }
        curr = curr->next;
    }
    printf(" -> NULL\n");
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
}

int count_nodes(Node *head) {
    int count = 0;
    Node *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

void test_reverse_list() {
    printf("\n=== TEST TASK #1: REVERSE LINKED LIST ===\n");
    
    printf("Test 1: Empty list\n");
    Node *list1 = NULL;
    printf("Original: ");
    print_list(list1);
    list1 = reverse_list(list1);
    printf("Reversed: ");
    print_list(list1);
    free_list(list1);
    
    printf("\nTest 2: Single element\n");
    Node *list2 = create_node(5);
    printf("Original: ");
    print_list(list2);
    list2 = reverse_list(list2);
    printf("Reversed: ");
    print_list(list2);
    free_list(list2);
    
    printf("\nTest 3: Two elements\n");
    Node *list3 = create_node(1);
    list3 = insert_back(list3, 2);
    printf("Original: ");
    print_list(list3);
    list3 = reverse_list(list3);
    printf("Reversed: ");
    print_list(list3);
    free_list(list3);
    
    printf("\nTest 4: Multiple elements (A->B->C->D)\n");
    Node *list4 = create_node(1);
    list4 = insert_back(list4, 2);
    list4 = insert_back(list4, 3);
    list4 = insert_back(list4, 4);
    printf("Original: ");
    print_list(list4);
    list4 = reverse_list(list4);
    printf("Reversed: ");
    print_list(list4);
    free_list(list4);
}

void test_partition_list() {
    printf("\n=== TEST TASK #2: PARTITION LINKED LIST ===\n");
    
    printf("Test 1: x=5, Original [3,5,8,5,10,2,1]\n");
    Node *list1 = create_node(3);
    list1 = insert_back(list1, 5);
    list1 = insert_back(list1, 8);
    list1 = insert_back(list1, 5);
    list1 = insert_back(list1, 10);
    list1 = insert_back(list1, 2);
    list1 = insert_back(list1, 1);
    
    printf("Original: ");
    print_list(list1);
    list1 = partition_list(list1, 5);
    printf("After partitioning around 5: ");
    print_list(list1);
    free_list(list1);
    
    printf("\nTest 2: All elements < x (x=10)\n");
    Node *list2 = create_node(1);
    list2 = insert_back(list2, 2);
    list2 = insert_back(list2, 3);
    printf("Original: ");
    print_list(list2);
    list2 = partition_list(list2, 10);
    printf("After partitioning around 10: ");
    print_list(list2);
    free_list(list2);
    
    printf("\nTest 3: All elements >= x (x=1)\n");
    Node *list3 = create_node(5);
    list3 = insert_back(list3, 10);
    list3 = insert_back(list3, 8);
    printf("Original: ");
    print_list(list3);
    list3 = partition_list(list3, 1);
    printf("After partitioning around 1: ");
    print_list(list3);
    free_list(list3);
    
    printf("\nTest 4: Single element (x=5)\n");
    Node *list4 = create_node(3);
    printf("Original: ");
    print_list(list4);
    list4 = partition_list(list4, 5);
    printf("After partitioning around 5: ");
    print_list(list4);
    free_list(list4);
}

int main() {
    printf("========================================\n");
    printf("PRACTICAL 11: DATA CONTAINERS\n");
    printf("Linked List Algorithms\n");
    printf("========================================\n");
    
    test_reverse_list();
    
    test_partition_list();
    
    printf("\n========================================\n");
    printf("All tests completed successfully!\n");
    printf("========================================\n");
    
    return 0;
}
