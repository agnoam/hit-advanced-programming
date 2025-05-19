#define _CRT_SECURE_NO_WARNINGS
 
/* Libraries */
#include <stdio.h>
#include <malloc.h>

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
void Ex1() {
	/* Called functions: 
		split, printStringsArray, freeMatrix */
	/* Write Code Here! */
}

void Ex2() {
	/* Called functions: 
		createFile, commonestLetter */
	/* Write Code Here! */
}

void Ex3() {
	/* Called functions:
		decode */
	/* Write Code Here! */
}

char** split(char letter, char* str, int* p_size) {
	/* Write Code Here! */
}

void createFile(char* filename) {
	/* Write Code Here! */
}

char commonestLetter(char* filename) {
	/* Write Code Here! */
}

void decode(char* text) {
	/* Write Code Here! */
}

/* Definitions of auxiliary functions */

/* ------------------- */