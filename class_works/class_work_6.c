#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char value;
    struct Node* next;
} Node;

/**
 * Prints the values of a linked list.
 * @param list Pointer to the head of the linked list.
 */
void print_linked_list(Node* list) {
    int is_first = 1;
    printf("(");
    
    while (list) {
        if (is_first) {
            printf("%c", list->value);
            is_first = 0;
        } else {
            printf(" -> %c", list->value);
        }

        list = list->next;
    }

    printf(")\n");
}

/**
 * Allocates a new node with the given value and next pointer.
 * 
 * This function allocates memory for a new node, assigns the provided value to the node's `value` field,
 * and sets the `next` field to the provided next pointer.
 * 
 * @param value The character value to store in the new node.
 * @param next A pointer to the next node in the list, or NULL if this is the last node.
 * 
 * @return A pointer to the newly allocated node.
 */
Node* allocate_node(char value, Node* next) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = next;

    return new_node;
}

/**
 * Generates a linked list of nodes, with possible duplicate characters at a specified interval.
 * 
 * This function creates a linked list of nodes where each node contains a character. Every `duplicate_interval`-th node
 * contains the same character as the previous node, effectively creating duplicates.
 * 
 * @param length The total length of the list to generate.
 * @param duplicate_interval The interval at which duplicates will occur in the list.
 * 
 * @return A pointer to the head of the newly created linked list.
 */
Node* generate_list_with_duplicates(int length, int duplicate_interval) {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < length; i++) {
        if (head == NULL) {
            head = tail = allocate_node('a' + i, NULL);
        } else {
            tail->next = allocate_node(!(i % duplicate_interval) ? 'a' + i : 'a' + (i-1), NULL);
            tail = tail->next;
        }
    }

    return head;
}

/**
 * Inserts a character into a sorted linked list.
 * 
 * This function traverses the list and inserts a new character into the list such that the list remains sorted.
 * The list is assumed to be sorted in ascending order, and the new character will be inserted at the appropriate position.
 * 
 * @param head A pointer to the head of the linked list.
 * @param new_char The new character to insert into the list.
 * 
 * @return A pointer to the head of the modified linked list.
 */
Node* insert_char(Node** head, char new_char) {
    Node* current_node = (*head);

    while (current_node) {
        Node* tail_node = current_node->next;
        if (current_node->value <= new_char && (!current_node->next || (tail_node && tail_node->value > new_char))) {
            Node* new_node = allocate_node(new_char, tail_node);
            current_node->next = new_node;
        }

        current_node = tail_node;
    }

    return (*head);
}

/**
 * Prompts the user to enter characters to create a linked list.
 * 
 * This function repeatedly asks the user to enter characters to create a linked list. The user can stop the process
 * by entering the character '0'. The function will return the head of the linked list created.
 * 
 * @return A pointer to the head of the linked list created from user input.
 */
Node* scan_linked_list() {
    Node* head = NULL;
    Node* tail = NULL;
    char input;

    do {
        printf("Enter a character (0 to stop): ");
        scanf("%c", &input);
        rewind(stdin); // Deleting the last \n

        if (input == '0')
            break;

        if (!head) {
            head = tail = allocate_node(input, NULL);
        } else {
            tail->next = allocate_node(input, NULL);
            tail = tail->next;
        }
    } while (input != '0');
    return head;
}

/**
 * Reverses the linked list.
 * 
 * This function reverses the order of nodes in the linked list by changing the direction of the `next` pointers.
 * After this operation, the head of the list will point to the last node in the original list.
 * 
 * @param head A pointer to the head of the linked list.
 */
void reverse_linked_list(Node** head) {
    if (head == NULL || *head == NULL)
        return;

    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;  // Store the next node
        current->next = prev;  // Reverse the current node's next pointer
        prev = current;        // Move prev and current one step forward
        current = next;
    }

    *head = prev;
}

int main() {
    // printf("Creating sorted list with duplicates:\n");
    // Node* sorted_list = generate_list_with_duplicates(5, 3);

    Node* sorted_list = scan_linked_list();
    printf("sorted_list: ");
    print_linked_list(sorted_list);

    insert_char(&sorted_list, 'c');
    printf("modified list: ");
    print_linked_list(sorted_list);

    reverse_linked_list(&sorted_list);
    printf("reversed list: ");
    print_linked_list(sorted_list);

    return 0;
}