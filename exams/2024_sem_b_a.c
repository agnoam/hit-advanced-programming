#include <stdio.h>
#include <stdlib.h>

typedef struct item {
    int digit;
    struct item* next;
} Item;

typedef struct {
    int size;
    int* ptr;
} dyn_array;

int numListCmp(Item* L1, Item* L2) {
    int diff = 0;
    while (L1 && L2) {
        diff = 1 + (L1->digit - L2->digit);

        L1 = L1->next;
        L2 = L2->next;
    }

    if (diff < 0)
        return -1;
    else if (diff > 0)
        return 1;
    return diff;
}

// Q2:
int* find_dividable_nums(int* numbers, int length, int divider, int* size) {
    int* dividable_nums = (int*) malloc(sizeof(int) * length);
    if (!dividable_nums) {
        fprintf(stderr, "Memory allocation failed!");
        *size = -1;
        return NULL;
    }

    *size = 0;
    for (int i = 0; i < length; i++) {
        if (!(numbers[i] % divider)) {
            dividable_nums[*size] = numbers[i];
            *size += 1;
        }
    }

    return dividable_nums;
}

dyn_array* divNumbers(int* A, int sz, int n) {
    dyn_array* result_array = (dyn_array*) malloc(sizeof(dyn_array) * n-1);
    if (!result_array) {
        fprintf(stderr, "Memory allocation failed!");
        return NULL;
    }

    for (int i = 0; i < n-1; i++) {
        int size = 0;
        int* sub_array = find_dividable_nums(A, sz, i+2, &size);
        result_array[i] = (dyn_array){ size, sub_array };
    }

    return result_array;
}
/*********************************************************************/

// Q3:
char get_char_at_position(FILE* file, long offset, long current_position) {
    char char_to_return;

    fseek(file, offset, SEEK_CUR);
    char_to_return = fgetc(file);
    fseek(file, current_position, SEEK_SET);
    
    return char_to_return;
}

int boggle(char *file_name, char *word) {
    long current_pos;
    char next, prev = '\0', current_char;
    
    FILE* file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Error occured, can not open the file");
        return -1;
    }

    while (*word && (current_char = fgetc(file)) != EOF) {
        current_pos = ftell(file);
        prev = get_char_at_position(file, -2, current_pos);
        
        if (current_char == *word) {
            word++;
            fseek(file, -1, SEEK_CUR);
        } else if (prev == *word) {
            word++;
            fseek(file, -2, SEEK_CUR);
        }
    }

    return !(*word);
}

/* 
    Q5: 
    a. Short answer: (4)
        Explanation:
            Let's evaluate each of the statements one by one and write what's it actually doing.
            1. `int a[5]` - Statically allocate sufficient memory for 5 integer elements in the stack (a will be a pointer to int array)
            2. `**p ... malloc(sizeof(int*))` - Dynamically allocate memory for single `int*`
            3. `*p = a` - Assigning the memory address of `a` (which in the stack) as the value of `p`
            4. `free(*p)` - Trying to free the memory of the **value of p** which is the pointer to a segment in the stack

            In 4, C will try to free the memory from the stack and will fail, because `free()` can be used just on the memory address whithin
            the range of the heap. so this mistaken operation, will cause the program to fail with runtime error (exception).
        
    b. Short answer: (1)
        Explanation:
            In C, the `^` operator stands for the XoR operation which is one of the base logical gates.
            In this question the operation is: `2 ^ 3`.
            
            Which actually means in simple terms: 
            1. Convert each number to it's binary representation
            2. Iterate each 2 bits and calculate the XoR of them
            3. Cast the binary value to what type you want

            So in this case `2` and `3` will be converted into:
            (2) = 10
            (3) = 11
            =========
            (1) = 01
*/

/* 
    Q6:
    Short answer: "24"
    Explanation:
        Let's revisite what we know about the `fgets` function.
        Function definition: `char* fgets(char* buffer, int char_count, FILE* file_pointer)`.

        What it does? - The function reads a string from a file stream, within specific character count.
        The character count is null-char included, so it will read from the file `char_count-1` characters.
        Eventually, before exiting the function it will seek the file pointer to the new position, and return the buffer pointer.
        
        So for example:
        Let's assume we have file with the content: `1234` and the `FILE* fp` is pointing the start of the file.
        So the return value of `fgets(st, 2, fp)` will be `['1', '\0']` in `char st[]`. and fp will seek one position forward.

        Let's look what it does in the provided code:
        1. `fgets(st, 2, fptr)` call in the `while` loop. 
            In this step the function reads from the file one letter, 
            seeking the `*fp` to the new position, and returning the *st pointer, (not null), so we continue into the while code block.
            
            Assumed state: `FILE* fp = 1` and `st = ['1', '\0']`.

        2. `fgets` as an argument for `fputs`:
            The function reads the next character and overwriting the existing *st content. 
            And moving and returning the same *st (which is still not null).

            The returned value will be written to `stdout` file (which presented in the terminal mostly).
            Assumed state: `FILE* fp = 2` and `st = ['2', '\0']`.
            Printed value: "2"

        3. Loops again in the while evaluation:
            Assumed state `FILE* fp = 3` and `st = ['3', '\0']`, and the returned value is non-null so entering again.

        4. Prints again to the `stdout`:
            Assumed state `FILE* fp = 4` and `st = ['4', '\0']`, 
            Printed value: "4"

        5. Evaluating again:
            The file pointer is moved over the last position of content in the file, so it will return NULL.
            Hence, the while code block won't run again.
        
        The program exits with the print "24" in the terminal.

*/

/* Auxiliary functions */

void _print_dyn_array(dyn_array* arr, int length) {
    printf("[\n");
    for (int i = 0; i < length; i++) {
        printf("(%d): [", i);
        for (int j = 0; j < arr[i].size; j++) {
            printf(j == arr[i].size-1 ? "%d" : "%d, ", arr[i].ptr[j]);
        }
        printf("]\n");
    }
}

/*************************************/

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
            break;

        case 2:
            int arr[] = { 15, 49, -8, 6, -25, 9, 10, -58, 1, 77 };
            int n = 5;
            dyn_array* output = divNumbers(arr, sizeof(arr) / sizeof(int), 5);
            printf("dividable numbers are: ");
            _print_dyn_array(output, n-1);
            break;

        case 3:
            char filename[] = "assets/boggle_example.dat";
            printf("is the word exists (should be 1): %d\n", boggle(filename, "baby"));
            printf("is the word exists (should be 1): %d\n", boggle(filename, "bag"));
            printf("is the word exists (should be 1): %d\n", boggle(filename, "byte"));
            printf("is the word exists (should be 0): %d\n", boggle(filename, "baq"));
            break;

        default:
            printf("There is no such question implemented, exiting.");
    }

    return 0;
}