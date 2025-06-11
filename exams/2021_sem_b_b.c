#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../black_box.c"

#define BUFFER_SIZE 200

typedef struct {
    char last_name[30];
    char first_name[30];
    unsigned id;
} Person;

typedef struct {
    int value;
    int target_col;
} MatrixCell;

typedef struct node {
    MatrixCell value;
    struct node *next;
} Node;

void files_merge(char* filename1, char* filename2, char* output_filename) {
    int output_arr[BUFFER_SIZE];
    int output_index = 0;
    
    FILE* file1 = fopen(filename1, "r");
    FILE* file2 = fopen(filename2, "r");
    FILE* output_file = fopen(output_filename, "w");
    if (!file1 || !file2 || !output_file) {
        fprintf(stderr, "Can not open required files: (file1: %s, file2: %s, file3: %s)", filename1, filename2, output_filename);
        fcloseall();
        return;
    }

    while (!feof(file1) || !feof(file2)) {
        int f1_current_number, f2_current_number;
        long f1_before_read = ftell(file1), f2_before_read = ftell(file2);
        char f1_current_char = getc(file1), f2_current_char = getc(file2);
        
        if ((f1_current_char != '\n' && !feof(file1)) || (f2_current_char != '\n' && !feof(file2))) {
            fseek(file1, -1, SEEK_CUR);
            fseek(file2, -1, SEEK_CUR);

            if (f1_current_char != '\n')
                fscanf(file1, "%d", &f1_current_number);
            if (f2_current_char != '\n')
                fscanf(file2, "%d", &f2_current_number);
                
            if ((f1_current_number < f2_current_number) && f1_current_char != '\n') {
                output_arr[output_index++] = f1_current_number;
                fseek(file2, f2_before_read, SEEK_SET);
            } else if ((f2_current_number < f1_current_number) && f2_current_char != '\n') {
                output_arr[output_index++] = f2_current_number;
                fseek(file1, f1_before_read, SEEK_SET);
            } else {
                output_arr[output_index++] = f1_current_number;
                output_arr[output_index++] = f2_current_number;
            }
        } else if (output_index) {
            for (int i = 0; i < output_index-1; i++)
                fprintf(output_file, "%d ", output_arr[i]);

            fputs("\n\n", output_file);
            fflush(output_file); // Writing the values to the disk
            output_index = 0;
        }
    }

    fclose(file1);
    fclose(file2);
    fclose(output_file);
}

int is_asc_order_array(Person* arr, int length) {
    for (int i = 0; i < length-1; i++) {
        int last_name_lexical_order = strcmp(arr[i].last_name, arr[i+1].last_name);
        
        // 1st argument greater than the 2nd argument
        if (last_name_lexical_order > 0) {
            return 0;
        } else if (last_name_lexical_order == 0) {
            // Family name are the same, so checking order of the 
            int first_name_lexical_order = strcmp(arr[i].first_name, arr[i+1].first_name);
            
            // Checking whether the first string is bigger than the second
            if (first_name_lexical_order > 0) {
                return 0;
            } else if (first_name_lexical_order == 0) {
                // Checking what number is bigger
                if (arr[i].id > arr[i+1].id)
                    return 0;
            }
        }
    }

    return 1;
}

int** matrix_init(int rows, int cols) {
    int** output_matrix = (int**) malloc(rows * sizeof(int*));
    if (!output_matrix) {
        fprintf(stderr, "Matrix allocation failed");
        return NULL;
    }
    
    for (int i = 0; i < rows; i++) {
        output_matrix[i] = (int*) calloc(cols, sizeof(int));
        if (!output_matrix[i]) {
            fprintf(stderr, "Row Matrix allocation failed");
            return NULL;
        }
    }

    return output_matrix;
}

int** efficient_storage_to_matrix(Node** A, int length, int output_cols) {
    int** output_matrix = matrix_init(length, output_cols);
    if (!output_matrix)
        return NULL;

    for (int i = 0; i < length; i++) {
        Node* iterator = A[i];
        while (iterator) {
            output_matrix[i][iterator->value.target_col] = iterator->value.value;
            iterator = iterator->next;
        }
    }

    return output_matrix;
}

/*
    Q4:
    1. Short answer: (4)
        Explanation:
            In C `static` and `global` variables will automatically initialized to 0.
            global variable: is a variable which declared outside the `main()` function (there is no keyword for such variable).
            `static` variable: is a varaible once declared in a function, it will hold it value across the function's invokations.
            (which makes this function "stateful" in programming jargon)
            So the value initializes to 0 for both cases automatically.

            We also see that x is declared twice, once as a global variable and once as static variable.
            We also know that the scope of the static `x` will overwrite the value in `f()` function's scope.

            In conclusion, the function will print the following:
            - `01` Which are the values of the static `x`
            - `01` This time for the global `x`
            - `12` The updated value of static `x` which retain it value from the previous  
    2. Short answer: (2)
        Explanation:
            This implementation mixing up for loop with the `>>` operator, let's dive in what is `>>` before.
            In C, The `>>` stands for the binary "shift-right" operation. 
            Which actually takes the left hand of the expression read it as binary string, 
            and removing as much elements as described in the left-hand of the expression (1 will divide by 2).
            So, the `>>=` stands for the operation "shift-right" operation with assignment to the left-hand variable.

            To interpret this code correctly, we need to figure out how much is `64` in binary (it's `1000000`).
            In each iteration of the loop, `i` will be divided by 2 because each time we will remove one bit from the 
            Least Segnificant Bit.
            So it will be printed sqrt(64) - 1 times, which equals to 7.

    3. Short answer: (3)
        Explanation:
            In C, the `realloc` function of 0 bytes will actually remove the data stored in `p`. and the realloc will return NULL.

    4. Short answer: (4)
        Explanation:
        `fread` and `fwrite` are functions that handles files using the given `FILE*` in their arguments.
        So there is no problem in any of this lines.

    5. Short answer: "1111222"
        Explanation:
        We can see here nested `printf()` functions. To accurately find the value, we should know what `printf()` returns.
        As the documentation of `printf()` suggests it returns the count of characters it was printing without the `'\0'`.

        So there are 4 executions of the `printf()`, and in each one it will print the content and will return the count
        of the printed carachters.
        
        The order of execution will be:
        1. 11 - The right-most print (printing `11` as one number)
        2. 11 - One to the left, the same.
        3. 22 - Prints two numbers, each time the count of the characters printed in 1, 2 executions.
        4. 2 - Prints one number, the count of operation 3.

        So the output will be: `"1111222"`.
*/

/* Auxiliary functions  */

Node* _construct_node(MatrixCell value, Node* next) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Node allocation failed");
        return NULL;
    }

    new_node->value = value;
    new_node->next = next;
    return new_node;
}

Node** _construct_efficient_storage(int matrix_rows, int matrix_cols, int max_elements) {
    srand(time(NULL)); // Seeding the random with actual timing

    Node** res = (Node**) calloc(matrix_rows, sizeof(Node));
    if (!res) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    while (max_elements) {
        int rand_row = rand() % ((matrix_rows-1) - 0 + 1) + 0;
        int rand_col = rand() % ((matrix_cols-1) - 0 + 1) + 0;
        int rand_value = rand() % ((10-1) - 1 + 1) + 1;

        Node* iterator = res[rand_row];
        if (!iterator) {
            res[rand_row] = _construct_node((MatrixCell) { rand_value, rand_col }, NULL);
            max_elements--;
        } else {
            while (iterator->next && iterator->value.target_col != rand_col) {
                iterator = iterator->next;
            }

            if (iterator->value.target_col != rand_col) {
                iterator->next = _construct_node((MatrixCell){ rand_value, rand_col }, NULL);
                max_elements--;
            }
        }
    }

    return res;
}

///////////////////////////////

int main() {
    int input;
    printf("Enter question number: ");
    scanf("%d", &input);

    switch (input) {
        case 1:
            char filename[] = "assets/testfile.txt";
            char filename2[] = "assets/testfile2.txt";
            char output_filename[] = "output.txt";
            
            files_merge(filename, filename2, output_filename);
            break;

        case 2:
            Person should_return_true[] = { 
                { "Asher", "Mike", 231567809 }, 
                { "Bern", "David", 216578900 }, 
                { "Borgman", "Joseph", 354678903 }, 
                { "Cohen", "Abraham", 224567821 }, 
                { "Cohen", "Den", 206666431 }, 
                { "Levi", "Ilan", 290876441 }, 
                { "Levi", "Omri", 245689432 }, 
                { "Levi", "Omri", 245689436 }, 
                { "Smith", "Jack", 345389010 }, 
                { "Smith", "John", 311232111 } 
            };
            int val = is_asc_order_array(should_return_true, sizeof(should_return_true) / sizeof(Person));
            printf("is_ascending order (should be 1): %d\n", val);
            
            Person should_return_false[] = { 
                { "Asher", "Mike", 231567809 }, 
                { "Bern", "David", 216578900 }, 
                { "Borgman", "Joseph", 354678903 }, 
                { "Cohen", "Abraham", 224567821 }, 
                { "Cohen", "Den", 206666431 }, 
                { "Levi", "Ilan", 290876441 }, 
                { "Levi", "Omri", 245689436 }, 
                { "Levi", "Omri", 245689432 }, 
                { "Smith", "Jack", 345389010 }, 
                { "Smith", "John", 311232111 } 
            };
            val = is_asc_order_array(should_return_false, sizeof(should_return_true) / sizeof(Person));
            printf("is_ascending order (should be 0): %d", val);
            break;

        case 3:
            int matrix_rows = 5, matrix_cols = 4;
            Node** efficient_storage = _construct_efficient_storage(5, 4, 5);
            int** matrix = efficient_storage_to_matrix(efficient_storage, matrix_rows, matrix_cols);
            printf("output matrix:\n");
            print_matrix(matrix, matrix_rows, matrix_cols);
            break;

        default:
            printf("There is no such question implemented, exiting.");
    }

	return 0;
}
