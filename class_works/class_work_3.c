#include <stdio.h>
#include <stdlib.h>
#include "../black_box.c"

///////////////////////////////////////////////////////////////////
int* allocate(int elements) {
    int* arr = malloc(elements * sizeof(int));
    if (!arr)
        return NULL;

    for (int i = 0; i < elements; i++)
        arr[i] = i + 1;

    return arr;
}
///////////////////////////////////////////////////////////////////

/**
 * Reallocates memory for a given memory block with a new size.
 * In case of allocation failure, the function will return NULL as result.
 *
 * @param memblock A pointer to the memory block to be reallocated.
 *                 If `memblock` is `NULL`, the function behaves like `malloc`.
 * @param size_old The size (in bytes) of the existing memory block pointed to by `memblock`.
 * @param size_new The size (in bytes) of the new memory block to be allocated.
 *
 * @returns A pointer to the newly allocated memory block. If memory allocation fails or
 *         if both `size_old` and `size_new` are zero, returns `NULL`. If `memblock` is `NULL`,
 *         a new block of memory is allocated with the size `size_new`.
 */
void* realloc1(void* memblock, unsigned size_old, unsigned size_new) {
    if (!size_old || !size_new)
        return NULL;

    void* new_block = malloc(size_new);
    if (!memblock)
        return new_block;

    // Cast the void pointers to unsigned char* because memory is copied byte-by-byte
    unsigned char* d = new_block;
    const unsigned char* s = memblock;

    if (!new_block)
        return memblock;

    // Copy byte-by-byte from source to destination
    for (size_t i = 0; i < (size_old < size_new ? size_old : size_new); i++)
        d[i] = s[i];

    free(memblock);
    return new_block;
}

/**
 * Concatenates two integer arrays into one.
 * If memory allocation fails, the function prints an error message and returns `NULL`.
 *
 * @param arr1 Pointer to the first integer array.
 * @param size1 The size of the first array (`arr1`), in terms of the number of elements.
 * @param arr2 Pointer to the second integer array to be appended to `arr1`.
 * @param size2 The size of the second array (`arr2`), in terms of the number of elements.
 *
 * @return A pointer to the newly concatenated array, which contains the elements of `arr1`
 *         followed by the elements of `arr2`. If memory allocation fails, returns `NULL`.
 */
int* arrcat(int* arr1, unsigned size1, int* arr2, unsigned size2) {
    int new_size = size1 + size2;
    int* reallocated_arr1 = (int*)realloc1(arr1, size1 * sizeof(int), new_size * sizeof(int));
    if (!reallocated_arr1) {
        printf("Memory allocation failed!");
        return NULL;
    }

    int new_length = new_size;
    int relative_index = 0;
    for (int i = size1; i < new_length; i++)
        reallocated_arr1[i] = arr2[relative_index++];

    return reallocated_arr1;
}

int main() {
    printf("Excersize A: \n");
    int length = 5;
    int* arr = allocate(length);
    print_array(arr, 5);

    // Add extra 4 elements
    int new_size = (length + 4) * sizeof(int);
    int* new_pointer = realloc1(arr, sizeof(int) * length, new_size);
    if (new_pointer) {
        print_array(new_pointer, new_size / sizeof(int));

        new_pointer[5] = 12;
        print_array(new_pointer, new_size / sizeof(int));
    }

    free(new_pointer);


    printf("\n\nExcersize B: \n");
    int* arr_a = allocate(length);
    int* arr_b = allocate(length);
    print_array(arr_a, length);
    print_array(arr_b, length);

    int* cat_arr = arrcat(arr_a, length, arr_b, length);
    printf("Contcatenated array is: ");
    print_array(cat_arr, 2 * length);

    free(cat_arr);
    free(arr_b);

    return 0;
}