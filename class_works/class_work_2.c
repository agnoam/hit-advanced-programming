#include <stdio.h>
#include <stdlib.h>
#include "../black_box.c"

/**
 * Splits an array into even and odd elements.
 * Allocates memory for the new arrays and sets their sizes.
 * Trims unused memory after allocation.
 *
 * @param A Input array of integers.
 * @param length Number of elements in A.
 * @param even_arr Pointer to store even numbers array.
 * @param odd_arr Pointer to store odd numbers array.
 * @param even_size Pointer to store the even array size.
 * @param odd_size Pointer to store the odd array size.
 */
void split_arr(int* A, int length, int** even_arr, int** odd_arr, int* even_size, int* odd_size) {
    int even_index = 0, odd_index = 0;
    *even_arr = (int*)calloc(length, sizeof(int));
    *odd_arr = (int*)calloc(length, sizeof(int));

    if (!(*even_arr) || !(*odd_arr)) {
        printf("Memory allocation error");
        return;
    }

    for (int i = 0; i < length; i++) {
        if (!(A[i] % 2)) (*even_arr)[even_index++] = A[i];
        else (*odd_arr)[odd_index++] = A[i];
    }

    // Trim down the end
    *even_arr = (int*)realloc(*even_arr, even_index * sizeof(int));
    *odd_arr = (int*)realloc(*odd_arr, odd_index * sizeof(int));

    *even_size = even_index;
    *odd_size = odd_index;
}

/**
 * Handles the splitting of an integer array into even and odd numbers.
 * Calls split_arr and prints the resulting arrays.
 * Uses print_arr to display the output.
 * 
 * Usage examples for using the `split_arr` function
 */
void split_arr_handler() {
   int arr[] = { 1, 2, 3, 4, 5, 6, 11, 14, 15, 17 };
   int* even_arr = NULL;
   int* odd_arr = NULL;
   int even_size, odd_size;

   split_arr(arr, sizeof(arr) / sizeof(int), &even_arr, &odd_arr, &even_size, &odd_size);
   printf("Even arr: \n");
   print_array(even_arr, even_size);
   printf("\n Odd arr: \n");
   print_array(odd_arr, odd_size);

   free(even_arr);
   free(odd_arr);
}

/**
 * Removes duplicate elements from a sorted array.
 * Allocates memory for a new array and returns the unique elements.
 * Adjusts the array size to fit the unique elements count.
 *
 * @param sorted_arr Input sorted array.
 * @param length Number of elements in sorted_arr.
 * @param set_length Pointer to store the new array size.
 * 
 * @return Pointer to the new array containing unique elements.
 */
int* RemoveDup(int* sorted_arr, int length, int* set_length) {
	int set_index = 0;
	int* set_arr = calloc(length, sizeof(int));

	if (!set_arr) {
		printf("Memory allocation error");
		return NULL;
	}

	for (int i = 0; i < length - 1; i++) {
		if (i == 0 || sorted_arr[i] != sorted_arr[0] && sorted_arr[i] != sorted_arr[i + 1])
			set_arr[set_index++] = sorted_arr[i];
	}

	if (sorted_arr[length - 2] != sorted_arr[length - 1])
		set_arr[set_index++] = sorted_arr[length - 1];

	*set_length = set_index;
	return (int*)realloc(set_arr, set_index * sizeof(int));
}

/**
 * Removes duplicate elements from a sorted array.
 * Allocates memory for a new array and returns the count of unique elements.
 * Adjusts the array size to fit the unique elements count.
 *
 * @param sorted_arr Input sorted array.
 * @param length Number of elements in sorted_arr.
 * @param set_arr Pointer to store the new array of unique elements.
 * 
 * @return Number of unique elements in the new array.
 */
int RemoveDup_2(int* sorted_arr, int length, int** set_arr) {
	int set_index = 0;
	*set_arr = calloc(length, sizeof(int));

	if (!(*set_arr)) {
		printf("Memory allocation error");
		return -1;
	}

	for (int i = 0; i < length - 1; i++) {
		if (i == 0 || sorted_arr[i] != sorted_arr[0] && sorted_arr[i] != sorted_arr[i + 1])
			(*set_arr)[set_index++] = sorted_arr[i];
	}

	if (sorted_arr[length - 2] != sorted_arr[length - 1])
		(*set_arr)[set_index++] = sorted_arr[length - 1];

	*set_arr = (int*)realloc(*set_arr, set_index * sizeof(int));
	return set_index;
}

/**
 * Removes duplicate elements from a sorted array.
 * Allocates memory for a new array and updates the size.
 * Adjusts the array size to fit the unique elements count.
 *
 * @param sorted_arr Input sorted array.
 * @param length Number of elements in sorted_arr.
 * @param set_arr Pointer to store the new array of unique elements.
 * @param set_length Pointer to store the count of unique elements.
 */
void RemoveDup_3(int* sorted_arr, int length, int** set_arr, int* set_length) {
	int set_index = 0;
	*set_arr = calloc(length, sizeof(int));

	if (!(*set_arr)) {
		printf("Memory allocation error");
		return;
	}

	for (int i = 0; i < length - 1; i++) {
		if (i == 0 || sorted_arr[i] != sorted_arr[0] && sorted_arr[i] != sorted_arr[i + 1])
			(*set_arr)[set_index++] = sorted_arr[i];
	}

	if (sorted_arr[length - 2] != sorted_arr[length - 1])
		(*set_arr)[set_index++] = sorted_arr[length - 1];

	*set_length = set_index;
	*set_arr = (int*)realloc(*set_arr, set_index * sizeof(int));
}

/**
 * Handles the removal of duplicates from a sorted array.
 * Calls different implementations of duplicate removal functions.
 * Prints the resulting unique element sets.
 * 
 * Usage example for each of the remove_dups varations
 */
void remove_dups_handler() {
    int src_arr[] = { 1,1,1,2,2,3,5 };
	int src_length = sizeof(src_arr) / sizeof(int);
	int set_length;

	int* set1 = RemoveDup(src_arr, src_length, &set_length);
	printf("Set 1: ");
	print_array(set1, set_length);

	int* set2 = NULL;
	int set2_length = RemoveDup_2(src_arr, src_length, &set2);
	printf("Set 2: ");
	print_array(set2, set_length);

	int* set3 = NULL;
	int set3_length;
	RemoveDup_3(src_arr, src_length, &set3, &set3_length);
	printf("Set 3: ");
	print_array(set2, set_length);

    free(set1);
    free(set2);
    free(set3);
}

int main() {
    split_arr_handler();
	remove_dups_handler();

	return 0;
}