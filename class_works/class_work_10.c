#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Swaps the values of two characters.
 *
 * This function exchanges the values pointed to by `a` and `b`.
 *
 * @param a Pointer to the first character.
 * @param b Pointer to the second character.
 */
void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Finds the index of the last occurrence of a character within a string.
 *
 * @param str A pointer to the null-terminated string to search within.
 * @param target The character to search for.
 * 
 * @return The index of the last occurrence of `target` in `str`,
 * or -1 if `target` is not found.
 */
int find_last_index(char* str, char target) {
    int i = 0;
    int last_index = -1;

    while (str[i]) {
        if (str[i] == target)
            last_index = i;

        i++;
    }

    return last_index;
}

/**
 * Swaps characters of two strings at corresponding indices until the end of the longer provided string is reached.
 *
 * @param str_a A pointer to the first null-terminated string.
 * @param str_b A pointer to the second null-terminated string.
 *
 * @note If the strings have different lengths, You must ensure that the memory allocated for both strings is sufficient for any potential changes due to swapping.
 */
void replace_strs(char* str_a, char* str_b) {
    int i = 0;
    while (str_a[i] || str_b[i]) {
        swap(str_a+i, str_b+i);
        i++;
    }
}

/**
 * Converts an integer index (0-15) to its hexadecimal character representation.
 *
 * @param index The integer index to convert (0-15).
 * @param is_capital Non-zero if the hexadecimal character should be uppercase,
 * zero for lowercase.
 * 
 * @return The hexadecimal character corresponding to the `index`.
 * Returns '0'-'9' for indices 0-9, and 'a'-'f' or 'A'-'F' for indices 10-15
 * based on the `is_capital` flag.
 */
char index_to_hex(int index, int is_capital) {
    if (index < 10)
        return '0' + index;
    
    return (index - 10) + (is_capital ? 'A' : 'a');
}

/**
 * Transforms a given string according to specific rules,
 * The exact rules can be found at the `class_work_10.pdf` provided in the project. 
 * The resulting transformed string replaces the original content in the input buffer.
 *
 * @param str Pointer to the string to be processed. Must be mutable and large enough to hold the expanded result.
 * 
 * @note The function allocates memory to store the processed string. It is crucial
 * that the original string's allocated memory is sufficient to hold the
 * potentially much longer processed string. The allocation size is based on
 * the worst-case scenario where every character could expand significantly.
 * If memory allocation fails, an error message is printed to stderr, and the
 * function returns without modifying the input string.
 */
void process_str(char* str) {
    int str_length = strlen(str);
    
    // Allocating for the worst case which is FF... which will make each charcter to be 15 characters long
    int processed_str_i = 0;
    char* processed_str = (char*) calloc(str_length * 15, sizeof(char));
    if (!processed_str) {
        perror("Memory allocation failed");
        return;
    }

    for (int i = 0; i < str_length; i++) {
        if (str[i] > 'f' && str[i] <= 'z') {
            // Computes the delta from 'a' to the given lower-case letter and adding the same delta to the capital letters
            processed_str[processed_str_i++] = 'A' + (str[i] - 'a');
        } else if (str[i] > 'F' && str[i] <= 'Z') {
            // Computes the delta from 'A' to the given capital letter and adding the same delta to the lower-case letters
            processed_str[processed_str_i++] = 'a' + (str[i] - 'A');
        } else if (str[i] >= '0' && str[i] <= '9') {
            // Iterating until the number count (so using the '0' as anchor to start the count from)
            // FYI: According to the rules of this function, the digit '0' won't be represented at all. Can you figure out why?
            for (int j = 1; j <= str[i] - '0'; j++)
                processed_str[processed_str_i++] = '0'+j;
        } else if (str[i] >= 'a' && str[i] <= 'f') {
            // Using the same trick as before, but now adding 10 to support "hex digits"
            int length = 10 + str[i] - 'a';
            for (int j = 1; j <= length; j++)
                processed_str[processed_str_i++] = index_to_hex(j, 0);
        } else if(str[i] >= 'A' && str[i] <= 'F') {
            // Using the same trick as before, but now adding 10 to support "hex digits"
            int length = 10 + str[i] - 'A';
            for (int j = 1; j <= length; j++)
                processed_str[processed_str_i++] = index_to_hex(j, 1);
        }
    }

    strcpy(str, processed_str);
}

int main() {
    char* str = "abcadeaxy";
    printf("\n last_index is: %d\n", find_last_index(str, 'a'));

    char str_a[] = "abc\0  ";
    char str_b[] = "bcdef\0";

    printf("str_a: %s, str_b: %s\n", str_a, str_b);
    replace_strs(str_a, str_b);
    printf("str_a: %s, str_b: %s\n", str_a, str_b);

    char str_c[] = "B$q0#3Me\0                                                    ";
    printf("input: %s\n", str_c);
    process_str(str_c);
    printf("output: %s\n", str_c);

    return 0;
}