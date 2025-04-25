/*
	Disclaimer:
	This code is not following the recommended `c` naming conventions, 
	in contrast to the rest of this repository. Because of the strict submition instructions.
*/

#define _CRT_SECURE_NO_WARNINGS
 
/* Libraries */
#include <stdio.h>
#include <malloc.h>
#include <math.h> // For using sqrt
#include <time.h> // For using random

/* Constant definitions */
#define N 3
#define ROWS 4
#define COLS 5

/* Type definitions */
typedef struct number {
	unsigned long long num;
	int sum;
} Number;

typedef struct triad {
	int i, j, value;
} Triad;

typedef struct item {
	Triad data;
	struct item* next;
} Item;

/* Function declarations */
void Ex1();
void Ex2();
void Ex3();

Number* primeSums(unsigned long long n1, unsigned long long n2, int* p_size);
int** matrixMaxNeighbor(int A[][COLS], int rows, int cols);
void createThreeLists(int** A, int rows, int cols, Item** pL1, Item** pL2);

/* Declarations of auxiliary functions */
// Ex1

int isPrime(int num);
int digitSum(unsigned long long num);
void printArray(Number* arr, int size);

// Ex2

int neighborMax(int A[][COLS], int rows, int cols, int i, int j);
int** allocMatrix(int rows, int cols);
void inputMatrix(int A[][COLS], int rows, int cols);
void printMatrix(int A[][COLS], int rows, int cols);
void printDynamicMatrix(int** A, int rows, int cols);
void freeMatrix(void** A, int rows);

// Ex3

Triad createThree(int i, int j, int value);
void inputDynamicMatrix(int** A, int rows, int cols);
void printList(Item* lst);
void freeList(Item* lst);
Item* insert(Item** head, Item* tail);

/* Custom function declarations */

void printError(const char *message);
Number* allocateNumber(unsigned long long num, int sum);
void appendNumber(Number** arr, Number* newNumber, int* currentLength, int* maxLength);
Item* createItem(Triad data, Item* next);

/* ------------------------------- */

/* Untouched code from template */
int main() {
	int select, i, all_Ex_in_loop = 0;
	
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
 * Reads a numeric range from standard input, finds all numbers within that range
 * whose digit sums are prime, prints the results, and frees allocated memory.
 */
void Ex1() {
	unsigned long long min, max;
	int arrLength;

	printf("Enter the range of number to search within (format - number number): ");
	scanf("%llu", &min);
	printf("Enter the limit number to search (number, not included): ");
	scanf("%llu", &max);

	Number* outputArr = primeSums(min, max, &arrLength);
	printArray(outputArr, arrLength);
	free(outputArr);
}

/**
 * Executes a demonstration of the neighbor-maximization process on a matrix.
 *
 * A static matrix of size ROWS×COLS is initialized to zero, then populated randomally. 
 * The original matrix is printed. A dynamic
 * matrix is then created, which replaces
 * each element with the maximum of its neighbors. The resulting matrix
 * is printed, and finally the allocated memory is released.
 */
void Ex2() {
	int** neighborsMatrix = NULL;

	int matrix[ROWS][COLS] = { 0 }; // Filling the matrix with 0's
	inputMatrix(matrix, ROWS, COLS);
	printf("The generated matrix is: ");
	printMatrix(matrix, ROWS, COLS);
	neighborsMatrix = matrixMaxNeighbor(matrix, ROWS, COLS);
	printf("The output matrix is: ");
	printDynamicMatrix(neighborsMatrix, ROWS, COLS);
	freeMatrix((void**) neighborsMatrix, ROWS);
}

/**
 * Interacting with the user to create and process a dynamic matrix, and output it as two linked lists.
 *
 * Prompts the user for the desired matrix dimensions, allocates a matrix, and displays it.
 * Let the user to populate the matrix, then prints the updated matrix.
 * Generates two linked lists based on matrix values, and prints both lists,
 * and finally the allocated memory is released.
 */
void Ex3() {
	int rows, cols;
	int** matrix = NULL;
	Item* list1 = NULL;
	Item* list2 = NULL;

	printf("Enter the number of rows and cols of the wanted matrix to allocate (number > 0 with space between them): ");
	scanf("%d%d", &rows, &cols);

	matrix = allocMatrix(rows, cols);
	printf("Allocated matrix before modification: ");
	printDynamicMatrix(matrix, rows, cols);
	
	inputDynamicMatrix(matrix, rows, cols);
	printf("Updated matrix is: ");
	printDynamicMatrix(matrix, rows, cols);

	createThreeLists(matrix, rows, cols, &list1, &list2);
	printf("The output lists are:\n");
	printf("list1: ");
	printList(list1);
	printf("list2: ");
	printList(list2);

	freeMatrix(matrix, rows);
	freeList(list1);
	freeList(list2);
}

/**
 * Builds an array of Number structs for all integers in the range [n1, n2)
 * whose digit sums are prime.
 *
 * @param n1 lower bound of the range (inclusive)
 * @param n2  upper bound of the range (exclusive)
 * @param arrLength pointer to an int where the count of returned elements will be stored
 * @return pointer to a dynamically allocated array of Number structs;
 *		the caller is responsible for freeing this memory
 */
Number* primeSums(unsigned long long n1, unsigned long long n2, int* arrLength) {
	int i, currentSum;
	Number* currentNum;
	
	Number* arr = NULL;
	int arrMaxSize;
	
	for (i = n1; i < n2; i++) {
		currentSum = digitSum(i);
		currentNum = allocateNumber(i, currentSum);

		if (isPrime(currentSum))
			appendNumber(&arr, currentNum, arrLength, &arrMaxSize);
	}

	return arr;
}

/**
 * Computes a new matrix of the same dimensions, where each element is
 * replaced by the maximum value among its neighbors in the input matrix.
 *
 * For each position (i, j) in the input matrix A, determine the largest value
 * among all adjacent cells (including diagonals) and stores it in
 * the corresponding position of the result matrix.
 *
 * @param A two-dimensional input array with dimensions [rows][cols]
 * @param rows number of rows in the input matrix
 * @param cols number of columns in the input matrix
 * @return pointer to a newly allocated rows×cols matrix containing
 * the maximum neighbor values, or NULL if allocation fails
 */
int** matrixMaxNeighbor(int A[][COLS], int rows, int cols) {
	int i, j;
	int** resultMatrix = allocMatrix(rows, cols);
	if (!resultMatrix)
		return NULL;

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++)
			resultMatrix[i][j] = neighborMax(A, rows, cols, i, j);
	}

	return resultMatrix;
}

/**
 * Scans a matrix with the given dimensions and populates two linked lists based on cell values:
 * 
 * - List 1 receives items for each cell where `A[i][j] == i + j`.
 * 
 * - List 2 receives items for each cell where `i < j` and `A[i][j] == j + |i - j|`.
 *
 * Each matching cell generates a new Item and inserted into the corresponding list.
 * The head pointers `pL1` and `pL2` are updated to reference the new list heads.
 *
 * @param A Pointer to a `rows`×`cols` matrix of integers.
 * @param rows Number of rows in matrix `A`.
 * @param cols Number of columns in matrix `A`.
 * @param pL1 Pointer to the head pointer of the first linked list. (treated as NULL)
 * @param pL2 Pointer to the head pointer of the second linked list. (treated as NULL)
 */
void createThreeLists(int** A, int rows, int cols, Item** pL1, Item** pL2) {
	int i, j, delta;
	Item* newItem;
	Item* currentL1Head = *pL1 = NULL;
	Item* currentL2Head = *pL2 = NULL;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			delta = abs(i - j);

			if (A[i][j] == i+j) {
				newItem = createItem(createThree(i, j, A[i][j]), NULL);
				currentL1Head = insert(!currentL1Head ? pL1 : &currentL1Head, newItem);
			} 
			
			if (i < j && A[i][j] == j + delta) {
				newItem = createItem(createThree(i, j, A[i][j]), NULL);
				currentL2Head = insert(!currentL2Head ? pL2 : &currentL2Head, newItem);
			}
		}
	}
}

/* Definitions of auxiliary functions */

/**
 * Prints an error message to the standard error stream with an "Error:" prefix.
 *
 * @param message  the error message to output
 */
void printError(const char *message) {
	fprintf(stderr, "Error: %s\n", message);
}

/**
 * Allocates memory for a Number struct and initializes its fields.
 *
 * @param num numeric value to assign to the struct
 * @param sum sum value to assign to the struct
 * @return pointer to the newly allocated Number struct, or NULL if allocation fails
 */
Number* allocateNumber(unsigned long long num, int sum) {
	Number* newNumber = malloc(sizeof(Number));
	if (!newNumber) {
		printError("Number struct allocation failed!");
		return NULL;
	}

	newNumber->num = num;
	newNumber->sum = sum;
	return newNumber;
}

/**
 * Appends a Number struct to a dynamically growing array, expanding its capacity as needed.
 *
 * @param arr address of the pointer to the `Number` array, may be NULL initially
 * @param newNumber pointer to the `Number` instance to append to the array
 * @param currentLength address of the variable tracking the current number of elements in the array
 * @param maxLength address of the variable tracking the allocated capacity of the array
 */
void appendNumber(Number** arr, Number* newNumber, int* currentLength, int* maxLength) {
	if (!(*arr)) {
		Number* newArr = (Number*) malloc(sizeof(Number));
		if (!newArr) {
			printError("Number struct array allocation failed!");
			return;
		}

		*maxLength = 1;
		*currentLength = 0;
		*arr = newArr;
	} else if (*currentLength == *maxLength) {
		Number* newArr = (Number*) realloc(*arr, sizeof(Number) * ((*maxLength) * 2));
		if (!newArr) {
			printError("Number struct array allocation failed!");
			return;
		}

		(*maxLength) *= 2;
		*arr = newArr;
	}

	/* 
		Elaboration about (**): 
			When using (**) - pointer to pointer
			It's important to refer to the inside array using this syntax `(*arr)[n]` specifically!.
			Else the compiler will try to set this at another variable.
			Because when writing `*arr[n]` it's actually translates into `*(arr + n)` 
			which will affect other variables by overwriting them and will cause exceptions.
	*/
	(*arr)[*currentLength] = *newNumber;
	(*currentLength)++;
}

/**
 * Recursively computes the sum of the digits of a given number.
 *
 * @param num the number whose digits will be summed
 * @return the sum of the digits of num
 */
int digitSum(unsigned long long num) {
	if (!num) 
		return 0;
	return (num % 10) + digitSum(num / 10);
}

/**
 * Determines whether a given integer is a prime number.
 *
 * @param num the integer to test for primality
 * @return 1 if num is prime, 0 otherwise
 */
int isPrime(int num) {
	int i, sqrtNum = ((int) sqrt((double) num)) + 1;
	
	for (i = 2; i < sqrtNum; i++) {
		if (!(num % i))
			return 0;
	}

	return 1;
}

/**
 * Prints the numeric values and their digit sums from an array of `Number` structs.
 *
 * @param arr pointer to the first element of the `Number` array
 * @param length number of elements in the array
 */
void printArray(Number* arr, int length) {
	int i;

	if (!arr) {
		printf("NULL\n");
		return;
	}

	printf("nums: [");
	for (i = 0; i < length; i++) {
		printf(i == length - 1 ? "%5d" : "%5d, ", arr[i].num);
	}
	printf("]\n");

	printf("sums: [");
	for (i = 0; i < length; i++) {
		printf(i == length - 1 ? "%5d" : "%5d, ", arr[i].sum);
	}
	printf("]\n");
}

/**
 * Fills a static matrix with random integer values.
 *
 * @param A the matrix to fill
 * @param rows the number of rows in the matrix
 * @param cols the number of columns in the matrix
 */
void inputMatrix(int A[][COLS], int rows, int cols) {
	int i, j, minElement = 1, maxElement = 20;
	printf("Filling the matrix (static array)");

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			A[i][j] = rand() % (minElement - maxElement + 1) + minElement;
		}
	}
}

/**
 * Prints the contents of a static matrix to the console.
 *
 * @param A the matrix to print
 * @param rows the number of rows in the matrix
 * @param cols the number of columns in the matrix
 */
void printMatrix(int A[][COLS], int rows, int cols) {
	int i, j;

	if (!A) {
		printf("NULL\n");
		return;
	}

	printf("[\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf(j == cols-1 ? "%3d" : "%3d, ", A[i][j]);
		}

		printf("\n");
	}
	printf("]\n");
}

/**
 * Prints the contents of a dynamically allocated matrix to the console.
 *
 * @param A the matrix to print
 * @param rows the number of rows in the matrix
 * @param cols the number of columns in the matrix
 */
void printDynamicMatrix(int **A, int rows, int cols) {
	int i, j;

	if (!A) {
		printf("NULL\n");
		return;
	}

	printf("[\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf(j == cols-1 ? "%3d" : "%3d, ", A[i][j]);
		}

		printf("\n");
	}
	printf("]\n");
}

/**
 * Gets the maximum value from an array of integers.
 *
 * @param arr the array to get the maximum from
 * @param len the length of the array
 * 
 * @return the maximum value in the array
 */
int getMax(int arr[], int len) {
	int i, max = INT_MIN;
	for (i = 0; i < len; i++)
		if (arr[i] > max) max = arr[i];
	
	return max;
}

/**
 * Finds the maximum neighbor value for a given element in a matrix.
 * 
 * It finds the maximum value within these positions of any given index if available: 
 * (top), (right), (bottom), (left) in this order
 *
 * @param A the matrix
 * @param rows the number of rows in the matrix
 * @param cols the number of columns in the matrix
 * @param i the row index of the element
 * @param j the column index of the element
 * 
 * @return the maximum neighbor value
 */
int neighborMax(int A[][COLS], int rows, int cols, int i, int j) {
	int neighbors[4] = { INT_MIN, INT_MIN, INT_MIN, INT_MIN };

	if (i > 0)
		neighbors[0] = A[i-1][j];
	if (j < cols-1)
		neighbors[1] = A[i][j+1];
	if (i < rows-1)
		neighbors[2] = A[i+1][j];
	if (j > 0)
		neighbors[3] = A[i][j-1];
				
	return getMax(neighbors, 4);
}

/**
 * Frees the memory allocated for a dynamically allocated matrix.
 *
 * @param A pointer to the matrix
 * @param rows the number of rows in the matrix
 */
void freeMatrix(void** A, int rows) {
	int i;
	for (i = 0; i < rows; i++) {
		if (A[i])
			free(A[i]);
	}

	free(A);
}

/**
 * Allocates memory for a dynamic matrix. 
 * 
 * The output matrix contains garbage values!
 *
 * @param rows the number of rows in the matrix
 * @param cols the number of columns in the matrix
 * 
 * @return a pointer to the allocated matrix, or NULL if allocation fails
 */
int** allocMatrix(int rows, int cols) {
	int i;
	int** matrix = (int**) calloc(rows, sizeof(int*));
	if (!matrix) {
		printError("Matrix allocation failed! (allocMatrix)");
		return NULL;
	}

	for (i = 0; i < rows; i++) {
		int* row = (int*) malloc(sizeof(int) * cols);
		if (!row) {
			printError("Matrix allocation failed! (allocMatrix)");
			freeMatrix((void**) matrix, rows);
			return NULL;
		}

		matrix[i] = row;
	}

	return matrix;
}

/**
 * Creates a `Triad` struct with the specified values.
 *
 * @param i row index for the triad
 * @param j column index for the triad
 * @param value integer value to store in the triad
 * @return a `Triad` struct initialized with the given indices and value
 */
Triad createThree(int i, int j, int value) {
	Triad three;
	three.i = i;
	three.j = j;
	three.value = value;
	
	return three;
}

/**
 * Allocates and initializes an Item node with the specified data and next pointer.
 *
 * @param data Triad containing the values to store in the new node.
 * @param next Pointer to the next Item in the list, or NULL if this is the last node.
 * @return Pointer to the newly allocated Item, or NULL if memory allocation fails.
 */
Item* createItem(Triad data, Item* next) {
	Item* newItem = (Item*) malloc(sizeof(Item));
	newItem->data = data;
	newItem->next = next;

	return newItem;
}

/**
 * Inserts an Item node into a singly linked list.
 *
 * @param head double pointer to the current list node (or list head when empty)
 * @param tail pointer to the Item node to insert
 * @return pointer to the inserted `Item` node (tail item)
 */
Item* insert(Item** head, Item* tail) {
	if (!(*head)) {
		*head = tail;
	} else {
		(*head)->next = tail;
	}

	return tail;
}

/**
 * Prompts the user to input values into a given dynamically allocated matrix.
 *
 * For each cell (i, j), displays a message requesting an integer and stores
 * the input in `A[i][j]`.
 *
 * @param A    pointer to an array of int pointers representing the matrix
 * @param rows number of rows in the matrix
 * @param cols number of columns in the matrix
 */
void inputDynamicMatrix(int** A, int rows, int cols) {
	int i, j, input;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("Enter the number in cell (%d, %d) (format - number): ", i, j);
			scanf("%d", &input);
			A[i][j] = input;
		}
	}
}

/**
 * Prints a list of `Triad` items in a formatted sequence.
 *
 * @param head Pointer to the head of the list.
 */
void printList(Item* head) {
	if (!head) {
		printf("NULL\n");
		return;
	}

	printf("(");
	while (head) {
		printf(
			head->next ? "[%d, %d, %d] -> " : "[%d, %d, %d]", 
			head->data.i, head->data.j, head->data.value
		);

		head = head->next;
	}
	printf(")\n");
}

/**
 * Deallocates all nodes in a linked list of `Item`.
 *
 * @param lst Pointer to the head of the list to free. If NULL, no action is taken.
 */
void freeList(Item* lst) {
	Item* lastItem;
	while (lst) {
		lastItem = lst;
		lst = lst->next;
		free(lastItem);
	}
}
