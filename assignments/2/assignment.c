/*
	Disclaimer:
	This code is not following the recommended `c` naming conventions, 
	in contrast to the rest of this repository. Because of the strict submition instructions.
*/
#define _CRT_SECURE_NO_WARNINGS
 
/* Libraries */
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/* Constant definitions */
#define N 3

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

char** split(char letter, char* str, int* p_size);
void createFile(char* filename);
char commonestLetter(char* filename);
void decode(char* text);

/* Declarations of auxiliary functions */

void printStringsArray(char** str_arr, int size);
void freeMatrix(void** A, int rows);

// Manually added

int is_same_letter(char a, char b);
char* init_dynamic_str(int length);
void append_char(char* str, char char_to_append, int pos, int max_length);
void* modify_arr_length(void* arr, size_t shrinked_size);

/* ------------------------------- */
int main() {
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");

	if (scanf("%d", &all_Ex_in_loop) == 1) {
		do {
			for (i = 1; i <= N; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");

			do {
				select = 0;
				printf("please select 0-%d : ", N);
				scanf("%d", &select);
			} while ((select < 0) || (select > N));

			switch (select) {
                case 1: 
                    Ex1(); 
                    break;

                case 2: 
                    Ex2(); 
                    break;

                case 3: 
                    Ex3(); 
                    break;
			}
		} while (all_Ex_in_loop && select);
    }

    return 0;
}


/* Function definitions */

/**
 * Implementation of the instructions of question 1
 * 
 * Split a hard-coded string which declared in the `char str[]` variable. 
 * The function will print all the words, which starting with the specified `letter`.
 * 
 * The function is case-insensitive
 */
void Ex1() {
	int p_size = -1;
    char str[] = "Rony Goodman got a good mark";
    char** splitted_arr = split('g', str, &p_size);
    if (!splitted_arr)
		return;

	printf("The array is: ");
    printStringsArray(splitted_arr, p_size);
	freeMatrix((void**) splitted_arr, p_size);
}

void Ex2() {
	/* Called functions: 
		createFile, commonestLetter */
	/* Write Code Here! */
}

/**
 * Implementation of the instructions of question 3
 * 
 * Demonstrates the usage of the decode function using hard-coded example which can be changed
 * by updating the `char str_to_decode[]`.
 * It initializes a string, prints its original state, decodes it using `decode()`,
 * and then prints the decoded string.
 */
void Ex3() {
    char str_to_decode[] = "bc8 d";
    printf("str before decoding: %s\n", str_to_decode);
    decode(str_to_decode);
    printf("str: %s\n", str_to_decode);
}

/**
 * Checking whether two characters are the same (case-insensitive)
 * 
 * @param a Given character
 * @param b Character to match against
 * 
 * @return Whether `a` and `b` are identical ('a' == 'A' || 'A' == 'a', etc.)
 */
int is_same_letter(char a, char b) {
	// The function is not case sensitive
	int a_delta = -1, b_delta = -1;
	if (a >= 'a' && a <= 'z') {
		a_delta = a - 'a';
	} else if (a >= 'A' && a <= 'Z') {
		a_delta = a - 'A';
	}

	if (b >= 'a' && b <= 'z') {
		b_delta = b - 'a';
	} else if (b >= 'A' && b <= 'Z') {
		b_delta = b - 'A';
	}

	if (a_delta == -1 || b_delta == -1)
		return a == b; // Exact match (including signs as well, such as: '$', '/', etc.)
	return a_delta == b_delta; // case-insensitive
}

/**
 * Allocate and initialize a dynamic string
 * 
 * @param length The wanted length of the buffer (all possible characters)
 * 
 * @return Pointer to the newly created string, In case of an error returns `NULL`
 */
char* init_dynamic_str(int length) {
	char* dynamic_str = (char*) calloc(length, sizeof(char));
	if (!dynamic_str) {
		perror("Failed to allocate dynamic string");
		return NULL;
	}
	
	return dynamic_str;
}

/**
 * Append character at the end of a given string, 
 * in case trying to modify outside the buffer the string will remain untouched
 * 
 * @param str The string to append to
 * @param char_to_append The character to append
 * @param pos The position of the new char to set
 * @param max_length The maximum buffer length of the string
 */
void append_char(char* str, char char_to_append, int pos, int max_length) {
	if (!str || pos >= max_length)
		return;

	str[pos] = char_to_append;
}

/**
 * Changes an array length to a specific size
 * 
 * @param arr The array to modify
 * @param shrinked_size The target size to save
 * 
 * @return A pointer to the newly reallocated array (can be the same one)
 */
void* modify_arr_length(void* arr, size_t shrinked_size) {
	void* shrinked_arr = realloc(arr, shrinked_size);
	if (!shrinked_arr) {
		perror("Array shrink failed!");
		return NULL;
	}

	return shrinked_arr;
}

/**
 * Splits a string into an array of substrings based on a given delimiter character (case-insensitive).
 *
 * The function iterates through the input string and identifies substrings that start with the
 * provided `letter`. These substrings are then stored in a dynamically allocated array.
 * The substrings include the delimiter character at the beginning.
 *
 * @param letter The delimiter character to split the string by (case-insensitive).
 * @param str The input string to be split.
 * @param arr_length A pointer to an integer that will store the number of substrings in the returned array.
 * If memory allocation for the final array fails, this value will be set to -1.
 *
 * @return A dynamically allocated array of strings (char**). Each element in the array is a
 * null-terminated string representing a substring. The caller is responsible for freeing
 * the memory allocated for this array and its elements when they are no longer needed.
 * Returns `NULL` if memory allocation fails at any point.
 */
char** split(char letter, char* str, int* arr_length) {
	int MAX_STR_LENGTH = strlen(str), return_arr_pos = 0;
	char** return_arr = (char**) malloc(MAX_STR_LENGTH * sizeof(char*)); // Allocate for worst case length
	if (!return_arr)
		return NULL;

	int read_index = 0, current_sub_str_pos = -1;
	char* sub_str = NULL;
	while (str[read_index]) {
		if (!sub_str && is_same_letter(str[read_index], letter)) {
			// Initialize new dynamic string and set the first character
			sub_str = init_dynamic_str(MAX_STR_LENGTH);
			current_sub_str_pos = 0;

			if (!sub_str) return NULL;
            sub_str[current_sub_str_pos++] = str[read_index];
		} else if (sub_str && str[read_index] != ' ') {
			// Append `read_index` character into the `sub_str`
			append_char(sub_str, str[read_index], current_sub_str_pos++, MAX_STR_LENGTH);
		} else if (sub_str || (sub_str && !str[read_index+1])) {
            // In case the current char is space or the last letter of the string
			sub_str = (char*) modify_arr_length(sub_str, (current_sub_str_pos + 1) * sizeof(char));
            if (!sub_str) return NULL;

            return_arr[return_arr_pos++] = sub_str; // Adding the shrinked str to the return arr
            sub_str = NULL;
		}

		read_index++;
	}

	*arr_length = return_arr_pos;
	char** shrinked_arr = (char**) modify_arr_length(return_arr, return_arr_pos * sizeof(char*));
	if (!shrinked_arr) 
		*arr_length = -1;

	return shrinked_arr;
}

void createFile(char* filename) {
	/* Write Code Here! */
}

char commonestLetter(char* filename) {
	/* Write Code Here! */
}

/**
 * Decodes a given text string in place.
 *
 * @param text A pointer to the null-terminated string to be decoded.
 * The string will be modified directly.
 */
void decode(char* text) {
	int i = 0, valid_char_count = 0;

	while (text[i]) {
		if (text[i] == ' ') {
			i++;
			
			/* 
				There is a mismatch between the question oreders and the example. 
				In order to match the function logic as the exact question instructions, you can comment the following line:
			*/
			valid_char_count = 0;
			continue;
		}
		
		text[i] -= (++valid_char_count);
		i++;
	}
}

/* Definitions of auxiliary functions */

/**
 * Prints an array of strings to the console.
 *
 * @param str_arr A pointer to an array of character pointers (strings).
 * @param size The number of strings in the array.
 */
void printStringsArray(char** str_arr, int size) {
	printf("[");
    for (int i = 0; i < size; i++)
        printf(i == size-1 ? "%s" : "%s, ", str_arr[i]);
    printf("]\n");
}

/**
 * Frees a dynamically allocated 2D matrix (array of pointers).
 *
 * @param A A pointer to the array of pointers representing the matrix.
 * @param rows The number of rows in the matrix.
 */
void freeMatrix(void** A, int rows) {
	for (int i = 0; i < rows; i++)
		free(A[i]);
	free(A);
}
/* ------------------- */