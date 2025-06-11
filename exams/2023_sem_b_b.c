#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>   // For time() to seed the random number generator

typedef struct node {
    int value;
    struct node* next;
} Node;

typedef struct {
    char film_code[10];
    int copies;
    int year;
} Film;

// Q1:
Node* JosephusPermutation(Node* lst, int m) {
    int i;
    Node* new_list_head = NULL;
    Node* new_list_tail = NULL;
    Node* iterator = NULL;

    // Iterate until there is one element left
    do {
        for (i = 0; i < m-1; i++) {
            iterator = !iterator ? lst : iterator->next;
        }
        
        if (!new_list_head) {
            new_list_tail = new_list_head = iterator->next;
        } else {
            new_list_tail->next = iterator->next;
            new_list_tail = iterator->next;
        }

        // Detaching the target node
        iterator->next = iterator->next->next;
    } while (iterator->next != iterator);
    
    // Adding the last node as the last element of the linked-list
    new_list_tail->next = iterator;
    iterator->next = NULL;
    return new_list_head;
}
/*********************************************************/

// Q2:
// `appropriateAppartment()` in the instructions file and `appropriateFilm` in online solutions
Film* appropriateFilm(char* fileName, int copies_limit, int last_year, int* size) {
    int current_index = 0;
    Film* output_array = NULL;
    FILE* file = fopen(fileName, "rb");
    Film buffer;
    
    *size = 0;
    if (!file) {
        fprintf(stderr, "Can not open the file");
        fclose(file);
        return NULL;
    }

    while (!feof(file)) {
        fread(&buffer, sizeof(Film), 1, file); // Reads one record
        if (buffer.year <= last_year && buffer.copies <= copies_limit)
            (*size)++;
    }


    output_array = (Film*) malloc((*size) * sizeof(Film));
    if (!output_array) {
        fprintf(stderr, "Output array memory allocation failed!");
        *size = 0;
        fclose(file);
        return NULL;
    }

    rewind(file); // Moving the pointer to the start of the file
    while (!feof(file)) {
        fread(&buffer, sizeof(Film), 1, file); // Reads one record
        if (buffer.year <= last_year && buffer.copies <= copies_limit)
            output_array[current_index++] = buffer;
    }
    *size = current_index;
    
    fclose(file);
    return output_array;
}
/*********************************************************/

// Q3:
int is_character(char character, char* separators) {
    while (*separators) {
        if (character == *separators)
            return 0;
        separators++;
    }

    return 1;
}

/**
 * This is stateful function!
 */
char* my_strtok(char* sentence, char* separators) {
    static char* _sentence;
    if (!sentence) {
        sentence = _sentence;
    }

    // Skip all separators
    while (!is_character(*sentence, separators)) {
        sentence++;
    }
    
    char* return_buffer = (char*) calloc(strlen(sentence), sizeof(char));
    int current_index = 0;
    while (is_character(*sentence, separators)) {
        return_buffer[current_index++] = *sentence;
        sentence++;
    }

    // Save the updated sentence in the backup ("state")
    _sentence = (char*) calloc(strlen(sentence), sizeof(char));
    strcpy(_sentence, sentence);

    if (!_sentence || !(*sentence))
        return NULL;
    return return_buffer;
}
/*********************************************************/

/*
    Q4: 
    Short answer: 
        p1 Print1: 20, bbb, aaa 
        p2 Print1: 20, bbb, aaa 
        
        p1 Print2: 20, bbb, Zaa 
        p2 Print2: 20, Zbb, Zaa 
        
        p1 Print3: 20, bbb, ZXa 
        p2 Print3: 222, ZXb, ZXa 

    Explanation:
        Let's annotate each row for better understanding this code. 
        The includes are ommited in this explanation.
        
        ```c
        #define SIZE 4

        struct TsT {
            int val1;
            char val2[SIZE];
            char* val3;
        };
        
        void func1(struct TsT myTsT) {
            myTsT.val3[1] = 'Y'; // p1.val3 is dynamically allocated string so this modification will affect the other instances too output: "ZYa"
            myTsT.val2[1] = 'Y'; // p1.val2 is statically allocated so it will affect the scope's instance only
            myTsT.val1 = 444; // This change is local too
        };

        void func2(struct TsT* myTsT) {
            myTsT->val3[1] = 'X'; // Remember! p2.val3 is dynamically allocated. output: "ZYa" will be converted into "ZXa"
            myTsT->val2[1] = 'X'; // Remember! p2.val2 is referenced from the main function, so it will change the parent variable value to: "ZXb"
            myTsT->val1 = 222; // Will change the values to 222
        };

        void main() {
            struct TsT p1, p2; // Two statically declared variables of TsT struct
            p1.val3 = (char*)malloc(4); // Allocating dynamic varaiable with size of 4 bytes (output will be a pointer)
            strcpy(p1.val3, "aaa"); // Copying the string "aaa\0" to the newly allocated dynamic string 
            p1.val1 = 20;
            strcpy(p1.val2, "bbb"); // Copying the string "bbb\0" to p1's `val2` variable which is static string with the length of 4 as well
            p2 = p1; // Overwriting all the values of `p2`
            printf("p1 Print1: %d, %s, %s \n", p1.val1, p1.val2, p1.val3); // output: "p1 Print1: 20, bbb, aaa"
            printf("p2 Print1: %d, %s, %s \n", p2.val1, p2.val2, p2.val3); // output: "p2 Print1: 20, bbb, aaa"
            p2.val2[0] = 'Z'; // Statically allocated variable 1st element modification, output: 'Zbb`
            p2.val3[0] = 'Z'; // Dynamically allocated variable 1st element modification, output: 'Zaa` (changed by pointer, so it will change `p1` too)
            printf("p1 Print2: %d, %s, %s \n", p1.val1, p1.val2, p1.val3); // output: "p1 Print2: 20, bbb, Zaa"
            printf("p2 Print2: %d, %s, %s \n", p2.val1, p2.val2, p2.val3); // output: "p1 Print2: 20, Zbb, Zaa"
            
            // func1 will duplicate the value of the struct to `func1()` scope, 
            // The static array will be duplicated into another variable, and the dynamic one will stay the same!
            func1(p1);
 
            func2(&p2); // func2 taking reference, so it will change both arrays.
            printf("p1 Print3: %d, %s, %s \n", p1.val1, p1.val2, p1.val3); // output: "p1 Print3: 20, bbb, Zxa"
            printf("p2 Print3: %d, %s, %s \n", p2.val1, p2.val2, p2.val3); // output: "p2 Print3: 222, ZXb ZXa"
        }
        ```
*/

/*
    Q5:
    a. Short answer: (4) is non-zero.
        Explanation:
        Let's explain what will be the output of each of the options and explain why.
        The printf function is constructed from `format` string and varaiable length of arguments (also called "variadic functions")
        The `format` is telling the function what type of data to print, and the variable after the ',' will be printed as the same format.

        (1).The format is: "%d" and the value is `0`. which stands for decimal. 
            so it will print a number that given an the array which is 0 so the output is '0'.
        (2).The format is: "%.0lf" and the value is `0.0`.
            which stans for long-float with 0 post-decimal point digits which won't print digits at all. 
            so `0.0` will be printed as '0'.
        (3). The format is: "%d" and the value is NULL. which holds the value of the memory address: 0,
            and because the format is "%d" so the function will print '0'.
        (4). The format is: "%d" and the value is `'0'`. 
            In this case the given value is a character which represents the sign '0'. 
            Which will convert into number due to the given format. which will be non-zero output.
        (5). The format is "%d" and the value is `EOF+1`.
            In this case the value is arithmetic operation between a constant in the language and a number.
            The EOF constant stands for EndOfFile flag which holds the value number: `-1`. 
            So C will evaluate the value of the arithmetic as: `-1+1` which equals to `0` and then will be printed as '0'.

    b. Short answer: (6).
        Explanation: This code shows a standard function calling vs. pointer-based function calling.
        Where the pointer-based function invoke is less common. this pattern used mostly when implmenting functions that uses callbacks
        or saving functions in data structures.

        Technically is the same, it's a reference to a function. which can be triggered using the trailing `()`.
        simple example: `myfunc()` === `(myfunc*)()` (logically equal).
        the pointer of the function is also callable.
*/

/*
    Q6: 
        Short answer: `"^^"`
        Explanation:
            Let's explore this bizzar print by braking it down to it's components.
            In C, the `^` operator stands for the XoR operation which is one of the base logical gates.
            Here is an example of usage: `A^b`.
            
            Which actually means in simple terms: 
            1. Convert each number to it's binary representation
            2. Iterate each 2 bits and calculate the XoR of them
            3. Cast the binary value to what type you want
            
            Now let's investigate the our case: `char s[]={'^','^','^'^'^','^'};`.
            As we clearly see, it's a static string definition. which holds 4 elements (2 elements surrounds each ',').
            Let's deep dive into the unique element have here. `'^'^'^'`. 
            It's pretty hard to distinguish how to correctly read it without the colorful IDE but let's look closer.
            We actually looks at '^' ^ '^' that's translated into `A ^ A` we discussed before.
            So we know that produces the value 0.

            Let's revisite `s` again. `char s[]={'^','^',0,'^'};`.
            Okay, so `printf("%s", ...)` should print a string which is null-terminated (ends with `'\0'`).
            So the function should iterate over the char array `s` 
            letter-by-letter and print it to the terminal until it encounters the `'\0'`.
            But wait a minute, `'\0'` === `0`, so we actually prints all the elements (letters) until the 0.
            Which are: the first two `'^'`, `"^^"`.
*/

/* Auxiliary functions (not in instructions) */

Node* _constrcut_node(int value, Node* next) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = next;

    return new_node;
}

Node* _construct_cycled_list(int n) {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 1; i <= n; i++) {
        Node* new_node = _constrcut_node(i, NULL);
        if (!head) {
            tail = head = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    tail->next = head;
    return head;
}

void _print_list(Node* head) {
    Node* backup = head;
    do {
        printf("(%d)->", head->value);
        head = head->next;
    } while (head != backup && head);
    printf("NULL\n");
}

void _free_list(Node* head) {
    Node* next;
    do {
        next = head->next;
        free(head);
        head = next;
    } while (head);
}

char* _generate_random_string(int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *random_string = malloc(sizeof(char) * (length + 1));
    if (random_string == NULL) {
        return NULL; // Memory allocation failed
    }
    for (int i = 0; i < length; i++) {
        int index = rand() % (sizeof(charset) - 1);
        random_string[i] = charset[index];
    }
    random_string[length] = '\0';
    return random_string;
}

void _create_films_file(char* filename, int num_of_films) {
    FILE* file = fopen(filename, "a");
    Film* buffer = (Film*) malloc(sizeof(Film));
    if (!file || !buffer) {
        fprintf(stderr, "Failed to allocate memory or opening the %s file", filename);
        return;
    }

    for (int i = 0; i < num_of_films; i++) {
        sprintf(buffer->film_code, "%s", _generate_random_string(10));
        buffer->copies = (i / 10)+1;
        buffer->year = 1999 + (i / 10)+1;
        fwrite(buffer, sizeof(Film), 1, file);
    }

    fclose(file);
}

void _print_array(Film* arr, int length) {
    for (int i = 0; i < length; i++) {
        Film f = arr[i];
        printf("id: %s, copies: %d, year: %d\n", f.film_code, f.copies, f.year);
    }
}

/********************************************/

/* 
    Disclaimer: The focus of those implementations are in the intruction-based functions implementations
    All the memory managment in the prefix `_` and the main functions are intentionally ignored
    To write less code as possible where it not actually needed.
*/
int main() {
    int input;
    printf("Enter question number to execute: ");
    scanf("%d", &input);

    switch (input) {
        case 1:
            Node* cycled_list = _construct_cycled_list(8);
            _print_list(cycled_list);

            Node* another_list = JosephusPermutation(cycled_list, 3);
            _print_list(another_list);
            _free_list(another_list);
            break;
        
        case 2:
            char filename[] = "movies.bin";
            int arr_length = 0;

            remove(filename);
            !errno && printf("Deleted last %s file\n", filename);

            _create_films_file(filename, 50);
            Film* arr = appropriateFilm(filename, 2, 2001, &arr_length);
            printf("Relevant films saved are:\n");
            _print_array(arr, arr_length);
            free(arr);
            break;

        case 3:
            char sentence[] = "     Why?! That's why.";
            char separators[] = "? !.";
            char* word;

            for (int i = 0; i < 4; i++) {
                word = my_strtok(i == 0 ? sentence : NULL, separators);
                printf("Word %d: %s\n", i+1, *word ? word : "NULL");
                free(word);
            }
            break;
            
        default:
            printf("There is no such question implemented, exiting.");
    }

    return 0;
}