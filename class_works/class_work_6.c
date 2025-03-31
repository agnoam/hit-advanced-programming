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

Node* allocate_node(char value, Node* next) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = next;

    return new_node;
}

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

Node* insert_char(Node** head, char new_char) {
    Node* current_node = (*head);

    while (current_node) {
        Node* tail_node = current_node->next;
        if (current_node->value <= new_char && (tail_node && tail_node->value > new_char)) {
            Node* new_node = allocate_node(new_char, tail_node);
            current_node->next = new_node;
        }

        current_node = tail_node;
    }

    return (*head);
}

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

int main() {
    // printf("Creating sorted list with duplicates:\n");
    // Node* sorted_list = generate_list_with_duplicates(5, 3);
    
    Node* sorted_list = scan_linked_list();
    printf("sorted_list: ");
    print_linked_list(sorted_list);

    insert_char(&sorted_list, 'c');
    printf("modified list: ");
    print_linked_list(sorted_list);

    return 0;
}