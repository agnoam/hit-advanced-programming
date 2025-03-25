#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

/**
 * Allocates and initializes a new node with the given value and next pointer.
 * 
 * @param value The value to be stored in the node.
 * @param next A pointer to the next node in the linked list.
 * 
 * @return Node* Pointer to the newly created node.
 */
Node* create_node(int value, Node* next) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    return node;
}

/**
 * Constructs two linked lists: one with even numbers and the other with odd numbers.
 * 
 * @param even_list Pointer to a pointer to the head of the even list.
 * @param odd_list Pointer to a pointer to the head of the odd list.
 */
void construct_lists(Node** even_list, Node** odd_list) {
    int input = -1;

    Node* even_last_pointer = *even_list;
    Node* odd_last_pointer = *odd_list;

    do {
        // For ingoring the first loop
        if (input != -1) {
            Node* new_node = create_node(input, NULL);

            if (!(input % 2)) {
                if (!even_last_pointer) {
                    even_last_pointer = new_node;
                } else {
                    even_last_pointer->next = new_node;
                    even_last_pointer = new_node;
                }
            } else {
                if (!odd_last_pointer) {
                    odd_last_pointer = new_node;
                } else {
                    odd_last_pointer->next = new_node;
                    odd_last_pointer = new_node;
                }
            }

            if (!(*even_list))
                *even_list = even_last_pointer;
            if (!(*odd_list))
                *odd_list = odd_last_pointer;
        }

        printf("Write positive number (or -1 to stop): ");
        scanf("%d", &input);
    } while (input != -1);
}

/**
 * Prints the values of a linked list.
 * @param list Pointer to the head of the linked list.
 */
void print_linked_list(Node* list) {
    int is_first = 1;
    printf("(");
    
    while (list) {
        if (is_first) {
            printf("%d", list->value);
            is_first = 0;
        } else {
            printf(" -> %d", list->value);
        }

        list = list->next;
    }

    printf(")\n");
}

/**
 * Frees the memory allocated for a linked list.
 * @param list Pointer to the head of the linked list to be freed.
 */
void free_list(Node* list) {
    Node* last_node = NULL;

    while (list) {
        last_node = list;
        list = list->next;

        free(last_node);
        last_node = NULL;
    }
}


int main() {
    Node* even_list = NULL;
    Node* odd_list = NULL;

    construct_lists(&even_list, &odd_list);
    printf("Even list: ");
    print_linked_list(even_list);
    printf("Odd list: ");
    print_linked_list(odd_list);

    // Disallocating the lists
    if (even_list) free_list(even_list);
    if (odd_list) free_list(odd_list);

    return 0;
}
