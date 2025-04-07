#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

/**
 * Creates a new node with the given value.
 * 
 * @param value The value to be stored in the node.
 * @return Pointer to the newly created node, or NULL if allocation failed.
 */
Node* create_node(int value) {
    Node* node = malloc(sizeof(Node));
    if (!node)
        return NULL;

    node->value = value;
    node->next = NULL;

    return node;
}

/**
 * Appends a new node to the end of a linked list.
 * 
 * @param tail A pointer to the address of the last node in the linked list.
 * @param new_node Pointer to the new node to be appended.
 * @return Pointer to the updated tail after the append operation.
 */
Node* append_after(Node** tail, Node* new_node) {
    if (*tail)
        (*tail)->next = new_node;
    
    *tail = new_node;
    return new_node;
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
            Node* new_node = create_node(input);
            if (!new_node) {
                fprintf(stderr, "Allocation failed for node with value %d\n", input);
                return;
            }

            if (!(input % 2))
                even_last_pointer = append_after(!(*even_list) ? even_list : &even_last_pointer, new_node);
            else
                odd_last_pointer = append_after(!(*odd_list) ? odd_list : &odd_last_pointer, new_node);
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

/**
 * Calcualtes the `sum`, `min` and `max values of the given linked list
 * 
 * @param head - The linked list head node
 * @param min - Pointer to the min variable to modify (auto initialize)
 * @param max - Pointer to the max variable to modify (auto initialize)
 * 
 * @returns The sum of the list
 */
int get_sum_min_max(Node* head, int* min, int* max) {
    int sum = 0;

    *min = INT_MAX;
    *max = INT_MIN;

    while (head) {
        sum += head->value;
        
        if (head->value < *min) *min = head->value;
        if (head->value > *max) *max = head->value;
        head = head->next;
    }

    return sum;
}

int main() {
    Node* even_list = NULL;
    Node* odd_list = NULL;
    int sum, min, max;

    construct_lists(&even_list, &odd_list);
    
    printf("Even list: ");
    print_linked_list(even_list);
    sum = get_sum_min_max(even_list, &min, &max);
    printf("sum: %d, min: %d, max: %d\n", sum, min, max);
    
    printf("Odd list: ");
    print_linked_list(odd_list);
    sum = get_sum_min_max(odd_list, &min, &max);
    printf("sum: %d, min: %d, max: %d\n", sum, min, max);
    

    // Disallocating the lists
    if (even_list) free_list(even_list);
    if (odd_list) free_list(odd_list);

    return 0;
}
