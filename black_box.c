/**
 * Prints an array of integers
 * 
 * @param arr An int pointer to the first element of the array
 * @param n The length of the given array
*/
void print_array(int* arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++)
        printf(i == n-1 ? "%d" : "%d, ", arr[i]);
    printf("]\n");
}

/**
 * Prints a matrix of integers
 * 
 * @param a A given matrix to display
 * @param rows Rows size of the matrix (for showing purposes)
 * @param cols Colmuns size of the matrix (for showing purposes)
 */
void print_matrix(int** a, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%4d ", a[i][j]);
        printf("\n");
    }
    printf("\n");
}