#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    Elaboration - triangular matrix:
        A triangular matrix is a term from the linear algebra.

        Definition of a triangular matrix:
        The matrix should be in NxN, which all the non-0 values will be in the range `j =< i` or `j >= i`.
        Where `j` stands for the columns and `i` stands for the rows indicators.
        Which will form an triangle like shape in the matrix.
        
        Example for lower triangular matrix:
            0 1 2 3 4
            ---------
        0 | 4 0 0 0 0 | 
        1 | 6 8 0 0 0 |
        2 | 9 1 3 0 0 |
        3 | 2 5 7 4 0 |
        4 | 1 7 3 8 1 |
            ---------
        
        Example for upper triangular matrix:
            0 1 2 3 4
            ---------
        0 | 4 7 1 2 3 |
        1 | 0 6 5 3 9 |
        2 | 0 0 1 6 8 |
        3 | 0 0 0 2 1 |
        4 | 0 0 0 0 5 |
            ---------
*/

/*
    Elaboration - callback function:
        A Callback function is actually a pointer/reference to a function that can be passed 
        into another function to be able to make a "generic function.
        In `c` we will have to make a typedef (more info can be found in the previous class_works),
        which will make an alias for a pointer that stands for a specific function with a specific arguments.
        
        For example:
        typedef <function's_return_type> (*<name_of_the_typedef>)(<...argument_list_of_the_function>);

        Usage example can be found at `print_trianglar_matrix` calls in the `main` function.
*/

/**
 * Definition of a callback function of the `get_element_*` functions.
 */
typedef int (*GetElementCallback)(int** triangular_memory, int row, int col);

/**
 * Generates a dynamically allocated lower triangular matrix with random integers.
 *
 * @param rows The number of rows for the triangular matrix.
 * @return A pointer to an array of int pointers representing the lower triangular matrix,
 * or `NULL` if memory allocation fails.
 */
int** generate_lower_triangular_matrix(int rows) {
    int** triangular_memory = (int**) malloc(sizeof(int*) * rows);
    if (!triangular_memory)
        return NULL;

    // Saving into the storage
    for (int i = 0; i < rows; i++) {
        int* cols_arr = (int*) malloc((sizeof(int) * i) + 1);
        if (!cols_arr)
            return NULL;

        triangular_memory[i] = cols_arr;
        for (int j = 0; j <= i; j++)
            cols_arr[j] = rand() % (1 - 9 + 1) + 1;
    }

    return triangular_memory;
}

/**
 * Retrieves an element from a lower triangular memory structure, returning 0 for out-of-bound upper elements.
 *
 * @param triangular_memory The 2D lower triangular memory structure.
 * @param row The row index of the desired element.
 * @param col The column index of the desired element.
 * 
 * @return The value at the specified position, or 0 if the column index exceeds the row index.
 */
int get_element_lower_triangular_memory(int** triangular_memory, int row, int col) {
    if (col > row)
        return 0;

    return triangular_memory[row][col];
}

/**
 * Generates a dynamically allocated upper triangular matrix with random integers.
 *
 * @param dimension_n The number of rows and columns for the square matrix.
 * @return A pointer to an array of int pointers representing the upper triangular matrix,
 * or `NULL` if memory allocation fails.
 */
int** generate_upper_triangular_matrix(int dimension_n) {
    int** triangular_memory = (int**) malloc(sizeof(int*) * dimension_n);
    if (!triangular_memory)
        return NULL;

    // Saving into the storage
    for (int i = 0; i < dimension_n; i++) {
        // Dimension N = number of cols and rows
        int* cols_arr = (int*) malloc((sizeof(int) * (dimension_n - i)));
        if (!cols_arr)
            return NULL;

        triangular_memory[i] = cols_arr;
        for (int j = 0; j < dimension_n - i; j++)
            cols_arr[j] = rand() % (1 - 9 + 1) + 1;
    }

    return triangular_memory;
}

/**
 * Retrieves an element from an upper triangular memory structure, returning 0 for out-of-bound lower elements.
 *
 * @param triangular_memory The 2D upper triangular memory structure.
 * @param row The row index of the desired element.
 * @param col The column index of the desired element.
 * 
 * @return The value at the specified position, or 0 if the column index is less than the row index.
 */
int get_element_upper_trianglar_memory(int** triangular_memory, int row, int col) {
    if (col < row)
        return 0;

    /* Because of the  */
    return triangular_memory[row][col-row];
}

/**
 * Prints a triangular matrix using a callback to retrieve its elements. 
 *
 * @param triangular_memory The 2D triangular memory structure to print.
 * @param dimension_n The number of rows and columns in the square matrix view.
 * @param get_element A callback function to retrieve elements from the matrix.
 */
void print_trianglar_matrix(int** triangular_memory, int dimension_n, GetElementCallback get_element) {
    printf("[\n");
    for (int i = 0; i < dimension_n; i++) {
        for (int j = 0; j < dimension_n; j++)
            printf("%d ", get_element(triangular_memory, i, j));
        printf("\n");
    }
    printf("]\n");
}

/**
 * Frees the memory allocated for a triangular memory.
 *
 * @param triangular_memory The 2D triangular memory to free.
 * @param rows The number of rows in the matrix.
 */
void free_triangle(int** triangular_memory, int rows) {
    for (int i = 0; i < rows; i++)
        free(triangular_memory[i]);
    free(triangular_memory);
}

int main() {
    int dimension_n = 5;

    printf("Generating matrices from %d order (it means %dx%d)\n", dimension_n, dimension_n, dimension_n);
    int** bottom_triangular_memory = generate_lower_triangular_matrix(dimension_n);
    if (!bottom_triangular_memory) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }
    
    printf("The lower triangular matrix is: ");
    print_trianglar_matrix(bottom_triangular_memory, dimension_n, get_element_lower_triangular_memory);

    int** top_triangular_memory = generate_upper_triangular_matrix(dimension_n);
    if (!top_triangular_memory) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    printf("The upper triangular matrix is: ");
    print_trianglar_matrix(top_triangular_memory, dimension_n, get_element_upper_trianglar_memory);
    
    free_triangle(bottom_triangular_memory, dimension_n);
    free_triangle(top_triangular_memory, dimension_n);
    return 0;
}