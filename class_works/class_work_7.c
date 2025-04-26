#include <stdio.h>
#include <stdlib.h>

/**
 * This function switches the position between two rows numbers.
 * 
 * The function should replace between the two rows in runtime complexity of O(1) 
 * for example the given integer matrix:
 * | 1, 2, 3, 4 |
 * | 4, 5, 6, 7 |
 * | 1, 2, 3, 4 |
 * 
 * and the rows are 1,2. So the output matrix will be
 * | 1, 2, 3, 4 |
 * | 1, 2, 3, 4 |
 * | 4, 5, 6, 7 |
 * 
 * 
 * @param matrix The given matrix
 * @param row_a The first row index to switch with
 * @param row_b The second row index to switch with
 */
void switch_rows(void** matrix, int row_a, int row_b) {
    /* Switch logic explanation:
        
        In order to switch between the rows within runtime complexity of `O(1)`
        We should understand the underlying structure of a matrix:

        We can think of matrix (2d array) as an array of pointers, 
        which each pointer is the first index of another whole new array,
        and each of the arrays is the actual row of the matrix.

        This simplification is shown in `int` for simple demonstration, 
        but it true for any other type (i.e. generics `void**`).

        We can simplify it into this:
        -> [ int* row_a, int* row_b]

        Actual example:
            int row_1 = { 1, 2, 3 };
            int row_2 = { 2, 2, 2 };
            int row_3 = { 1, 2, 3 };
            int** matrix = { row_1, row_2, row_3 };

        which will output:
            | 1 2 3 |
            | 2 2 2 |
            | 1 2 3 |

        Due this, we actually can switch between the rows within runtime complexity of `O(1)`.
        Because the steps are:
            1. Access to `matrix[row_b]` and copy it into a temp pointer [O(1)]
            2. Overwrite the `matrix[row_b]` with the pointer of `row_a` [O(1)]
            3. Overwrite the `matrix[row_a]` with the pointer of `temp` [O(1)]
    */

    // Used `void*` to perform generic pointer copy
    void* temp_row = matrix[row_b];
    matrix[row_b] = matrix[row_a];
    matrix[row_a] = temp_row;
}

/**
 * Constructs a 2D matrix of integers.
 *
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * 
 * @return A pointer to the allocated matrix, or NULL if memory allocation fails.
 */
int** construct_matrix(int rows, int cols) {
    int counter = 1;
    int** arr = (int**) malloc(rows * sizeof(int*));
    if (!arr) {
        fprintf(stderr, "Matrix allocation failed\n");
        return NULL;
    }

    for (int row = 0; row < rows; row++) {
        arr[row] = (int*) malloc(cols * sizeof(int));
        if (!arr[row]) {
            fprintf(stderr, "Matrix allocation failed\n");
            return NULL;
        }

        for (int col = 0; col < cols; col++)
            arr[row][col] = counter++;
    }

    return arr;
}

/**
 * Prints a 2D matrix of integers.
 *
 * @param matrix A pointer to the 2D matrix to be printed.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 */
void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("| ");
        for (int j = 0; j < cols; j++)
            printf("%d ", matrix[i][j]);
        printf("|\n");
    }
}

/**
 * Switching between two provided columns
 * The function assumes the matrix is always in dimensions of NxN (rows = columns)
 * 
 * @param matrix The matrix to alter
 * @param rows The number of the rows in the matrix
 * @param col_a The index of the column to switch
 * @param col_b The index of the second column to switch with
 */
void switch_cols(int** matrix, int rows, int col_a, int col_b) {
    int temp;

    for (int row = 0; row < rows; row++) {
        temp = matrix[row][col_b];
        matrix[row][col_b] = matrix[row][col_a]; // Replacing col_b with a
        matrix[row][col_a] = temp;
    }
}

int main() {
    int** matrix = construct_matrix(3, 3);
    if (!matrix)
        exit(ENOMEM); // Error - memory allocation failed

    printf("Original matrix: \n");
    print_matrix(matrix, 3, 3);
    switch_rows((void**) matrix, 1, 2);
    
    printf("\nSwitched matrix: \n");
    print_matrix(matrix, 3, 3);

    printf("\nColumns switched matrix: \n");
    switch_cols(matrix, 3, 1, 2);
    print_matrix(matrix, 3, 3);
    
    return 0;
}