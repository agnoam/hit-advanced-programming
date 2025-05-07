#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    Elaboration:
    A triangle bottom matrix is a term from the linear algebra.

    Definition of a triangle matrix:
    The matrix should be in NxN

    Example for bottom triangle matrix:
        0 1 2 3 4
        ---------
    0 | 4 0 0 0 0 | 
    1 | 6 8 0 0 0 |
    2 | 9 1 3 0 0 |
    3 | 2 5 7 4 0 |
    4 | 1 7 3 8 1 |
        ---------
    
    Example for top triangle matrix:
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
* Definition of a callback function of the "get_element" functions, which helps in writing less code
*/
typedef int (*GetElementCallback)(int** triangle_memory, int row, int col);

/**
 * Generate bottom triangle matrix and returning memory efficient matrix representation
 */
int** generate_bottom_triangle_matrix(int rows) {
    int** triangle_memory = (int**) malloc(sizeof(int*) * rows);
    if (!triangle_memory)
        return NULL;

    // Saving into the storage
    for (int i = 0; i < rows; i++) {
        int* cols_arr = (int*) malloc((sizeof(int) * i) + 1);
        if (!cols_arr)
            return NULL;

        triangle_memory[i] = cols_arr;
        for (int j = 0; j <= i; j++)
            cols_arr[j] = rand() % (1 - 9 + 1) + 1;
    }

    return triangle_memory;
}

int get_element_bottom_triangle(int** triangle_memory, int row, int col) {
    if (col > row)
        return 0;

    return triangle_memory[row][col];
}

int** generate_top_triangle_matrix(int dimension_n) {
    int** triangle_memory = (int**) malloc(sizeof(int*) * dimension_n);
    if (!triangle_memory)
        return NULL;

    int dummy = 1;
    // Saving into the storage
    for (int i = 0; i < dimension_n; i++) {
        // Dimension N = number of cols and rows
        int* cols_arr = (int*) malloc((sizeof(int) * (dimension_n - i)));
        if (!cols_arr)
            return NULL;

        triangle_memory[i] = cols_arr;
        for (int j = 0; j < dimension_n - i; j++)
            cols_arr[j] = dummy++;
            // cols_arr[j] = rand() % (1 - 9 + 1) + 1;
    }

    return triangle_memory;
}

int get_element_top_triangle(int** triangle_memory, int row, int col) {
    if (col < row)
        return 0;

    return triangle_memory[row][col-row];
}

void print_triangle_matrix(int** triangle_memory, int dimension_n, GetElementCallback get_element) {
    printf("[\n");
    for (int i = 0; i < dimension_n; i++) {
        for (int j = 0; j < dimension_n; j++)
            printf("%3d ", get_element(triangle_memory, i, j));
        printf("\n");
    }
    printf("]\n");
}

/**
 * This function assume the
 */
int free_triangle(int** triangle_memory, int rows) {
    for (int i = 0; i < rows; i++)
        free(triangle_memory[i]);
    free(triangle_memory);
}

int main() {
    int dimension_n = 5;
    int** bottom_triangle_memory = generate_bottom_triangle_matrix(dimension_n);
    if (!bottom_triangle_memory) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }
    
    print_triangle_matrix(bottom_triangle_memory, dimension_n, get_element_bottom_triangle);

    int** top_triangle_memory = generate_top_triangle_matrix(dimension_n);
    if (!top_triangle_memory) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    print_triangle_matrix(top_triangle_memory, dimension_n, get_element_top_triangle);
    
    free_triangle(bottom_triangle_memory, dimension_n);
    free_triangle(top_triangle_memory, dimension_n);
    return 0;
}