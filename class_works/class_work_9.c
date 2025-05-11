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
 * Reverses the given string in place by swapping mismatched characters from both ends.
 *
 * This function iterates over the string from both ends toward the center, swapping characters
 * only when they differ. It modifies the string in place and returns whether any changes occurred.
 *
 * @param str Pointer to the null-terminated string to reverse.
 * @return 1 if any characters were swapped, 0 if the string was already symmetric.
 */
int reverse_str(char* str) {
    int left = 0;
    int right = strlen(str) - 1;
    int is_changed = 0;

    while (left <= right) {
        if (*(str+left) != *(str+right)) {
            swap(str+left, str+right);
            is_changed = 1;
        }

        left++;
        right--;
    }

    return is_changed;
}

/**
 * Analyzes a string and counts occurrences of lowercase letters, uppercase letters, digits, and other characters.
 *
 * This function iterates over the input string and updates the counters for lowercase letters,
 * uppercase letters, digits, and all other (non-alphanumeric) characters.
 *
 * @param str Pointer to the null-terminated input string to analyze.
 * @param lower_count Pointer to an integer where the count of lowercase letters will be stored (pointers can be unintialized).
 * @param upper_count Pointer to an integer where the count of uppercase letters will be stored (pointers can be unintialized).
 * @param digit_count Pointer to an integer where the count of digit characters will be stored (pointers can be unintialized).
 * @param sign_count Pointer to an integer where the count of non-alphanumeric characters will be stored (pointers can be unintialized).
 */
void analyze_str(char* str, int* lower_count, int* upper_count, int* digit_count, int* sign_count) {
    int i = 0; 

    // Setting all the counts to zero
    *lower_count = *upper_count = *digit_count = *sign_count = 0;
    
    while (*(str+i)) {
        char current_char = *(str+i);
        if (current_char >= 'a' && current_char <= 'z')
            (*lower_count)++;
        else if (current_char >= 'A' && current_char <= 'Z')
            (*upper_count)++;
        else if (current_char >= '0' && current_char <= '9')
            (*digit_count)++;
        else
            (*sign_count)++;

        i++;
    }
}

/**
 * Collapses multiple consecutive spaces in a string into single spaces, in place.
 *
 * This function scans the input string and removes redundant spaces by shifting
 * non-space characters forward. As a result, sequences of two or more spaces are
 * replaced by a single space. The operation is performed in-place without using
 * additional memory.
 *
 * Example:
 * Input:  "Hello   world   !"
 * Output: "Hello world !"
 *
 * @param str Pointer to the null-terminated string to process.
 */
void shrink_spaces(char* str) {
    int read = 0, write = 0;
    int space_seen = 0;

    while (str[read]) {
        if (str[read] != ' ') {
            str[write++] = str[read];
            space_seen = 0;
        } else if (!space_seen) {
            str[write++] = ' ';
            space_seen = 1;
        }
        read++;
    }

    // Null-terminate the new string
    str[write] = '\0';
}

int main() {
    int input;
    printf("Enter question number: ");
    scanf("%d", &input);
    
    /* 
        Important to set this str as an array to be able to change it later in the code.
        In `c`, when we set up `char* str = "abc";` 
        it will be saved as a "string literal" which actually saved in the read only memory.
    */
    switch (input) {
        case 1:
            char str[] = "abcfa"; // Should output: "afcba"
            int is_changed = reverse_str(str);
            printf("reversed text: %s, is_changed: %d", str, is_changed);
            break;
        
        case 2:
            char str2[] = "abcABC123!@#"; // Should output: "3 lowers 3 uppers 3 digits 3 signs"
            int lowers, uppers, digits, signs;
            analyze_str(str2, &lowers, &uppers, &digits, &signs);
            printf("The provided string has: \nlowers: %d, \nuppers: %d, \ndigits: %d, \nsigns: %d", lowers, uppers, digits, signs);
            break;

        case 3:
            char str3[] = "I       live in    my Home"; // Should output "I live in my Home"
            shrink_spaces(str3);
            printf("Shrinked spaces: %s", str3);    
            break;
    }

    return 0;
}