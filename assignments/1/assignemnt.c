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
// EX1
int isPrime(int num);
int digitSum(unsigned long long num);
void printArray(Number* arr, int size);

// EX2
int neighborMax(int A[][COLS], int rows, int cols, int i, int j);
int** allocMatrix(int rows, int cols);

Triad createThree(int i, int j, int value);

/* Custom function declarations */
void printError(const char *message);
Number* allocateNumber(unsigned long long num, int sum);
void appendNumber(Number** arr, Number* newNumber, int* currentLength, int* maxLength);

void inputMatrix(int A[][COLS], int rows, int cols);
void printMatrix(int A[][COLS], int rows, int cols);
void printDynamicMatrix(int** A, int rows, int cols);
void freeMatrix(void** A, int rows);
void inputDynamicMatrix(int** A, int rows, int cols);
void printList(Item* lst);
void freeList(Item* lst);

/* ------------------------------- */

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

void Ex3() {
	/* Called functions: 
		allocMatrix, inputDynamicMatrix, printDynamicMatrix, createThreeLists, printList, freeMatrix, freeList */
	/* Write Code Here! */
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

void createThreeLists(int** A, int rows, int cols, Item** pL1, Item** pL2) {
	/* Called functions:
		createThree, insert */
	/* Write Code Here! */
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
		Warning: When using (**) - pointer to pointer
		It's important to refer to the inside array using this syntax `(*arr)[]`.
		Else the compiler will try to set this at another variable
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

void inputMatrix(int A[][COLS], int rows, int cols) {
	int i, j, minElement = 1, maxElement = 20;
	printf("Filling the matrix (static array)");

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			A[i][j] = rand() % (minElement - maxElement + 1) + minElement;
		}
	}
}

void printMatrix(int A[][COLS], int rows, int cols) {
	int i, j;

	printf("[\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf(j == cols-1 ? "%3d" : "%3d, ", A[i][j]);
		}

		printf("\n");
	}
	printf("]\n");
}

void printDynamicMatrix(int **A, int rows, int cols) {
	int i, j;

	printf("[\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf(j == cols-1 ? "%3d" : "%3d, ", A[i][j]);
		}

		printf("\n");
	}
	printf("]\n");
}

int getMax(int arr[], int len) {
	int i, max = INT_MIN;
	for (i = 0; i < len; i++)
		if (arr[i] > max) max = arr[i];
	
	return max;
}

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

void freeMatrix(void** A, int rows) {
	int i;

	for (i = 0; i < rows; i++) {
		if (A[i])
			free(A[i]);
	}

	free(A);
}

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
