#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct monom {
    double coefficient;
    int power;
} Monom;

typedef struct item {
    Monom mon;
    struct item* next;
} Item;

Item* create_item(Monom mon, Item* next) {
    Item* new_item = (Item*) malloc(sizeof(Item));
    if (!new_item) {
        fprintf(stderr, "Item memory allocation failed!");
        return NULL;
    }

    new_item->mon = mon;
    new_item->next = next;
    return new_item;
}

int find_max_power(Item* L) {
    int max = L->mon.power;
    while (L) {
        if (L->mon.power > max)
            max = L->mon.power;

        L = L->next;
    }

    return max;
}


Item* createPolynom(Item* L) {
    int elements_count = find_max_power(L) + 1; // Including the 0 power
    double* polynom_elements_arr = (double*) calloc(elements_count, sizeof(double));
    if (!polynom_elements_arr) {
        fprintf(stderr, "Elements array memory allocation failure!");
        return NULL;
    }

    Item* iterator = L;
    while (iterator) {
        polynom_elements_arr[iterator->mon.power] += iterator->mon.coefficient;
        iterator = iterator->next;
    }

    Item* list_to_return = NULL;
    for (int i = elements_count-1; i >= 0; i--) {
        if (!polynom_elements_arr[i])
            continue;

        Monom monom = { polynom_elements_arr[i], i };
        Item* new_item = create_item(monom, NULL);
        
        if (!list_to_return) {
            list_to_return = new_item;
            iterator = list_to_return;
        } else {
            iterator->next = new_item;
            iterator = iterator->next;
        }
    }

    return list_to_return;
}

int arrSorted(int* a, int n) {
    for (int i = 0; i < n-1; i++) {
        if (a[i] >= a[i+1])
            return 0;
    }

    return 1;
}

int columnSorted(int** ar, int m, int col) {
    for (int i = 0; i < m-1; i++) {
        if (ar[i][col] >= ar[i+1][col])
            return 0;
    }

    return 1;
}

void sortedRowsCols(
    int **ar, 
    int m, 
    int n, 
    int **ar_s_rows, 
    int *num_s_rows, 
    int **ar_s_cols, 
    int *num_s_cols
) {
    int current_index = 0;

    *ar_s_rows = (int*) malloc(sizeof(int) * m);
    *ar_s_cols = (int*) malloc(sizeof(int) * n);
    if (!(*ar_s_cols) || !(*ar_s_rows)) {
        fprintf(stderr, "Result array memory allocation failed");
        return;
    }

    for (int i = 0; i < m; i++) {
        if (arrSorted(ar[i], n))
            (*ar_s_rows)[current_index++] = i;
    }

    *num_s_rows = current_index;
    current_index = 0;

    for (int i = 0; i < n; i++) {
        if (columnSorted(ar, m, i))
            (*ar_s_cols)[current_index++] = i;
    }

    *num_s_cols = current_index;
}

int is_character(char a, char* separators){
    int num_of_separators = strlen(separators);
    for (int j = 0; j < num_of_separators; j++){
        if (!a || a == separators[j]) {
            return 0;
        }
    }

    return 1;
}

char* nextWord(char* sentence, char* separators, char* word) {
    int i = 0;
    int word_index = 0;

    while (is_character(sentence[i], separators)) {
        word[word_index++] = sentence[i++];
    }
    word[word_index] = '\0';

    // Finding the first letter of the next word
    while (!is_character(sentence[i], separators) && sentence[i]) {
        i++;
    }

    char* next_word = sentence + i;
    return !(*(next_word)) ? NULL : next_word;
}

int breakSentence(char* sentence, char* separators, char* file_name) {
    FILE* file = fopen(file_name, "a");
    if (!file) {
        fprintf(stderr, "Can not access the file");
        return -1;
    }

    int max_length = strlen(sentence);
    char* current_word = (char*) malloc(sizeof(char) * max_length);
    if (!current_word) {
        fprintf(stderr, "Word buffer allocation failed");
        return -1;
    }

    int word_count = 0;
    char* next_word = nextWord(sentence, separators, current_word);
    while (current_word) {
        fprintf(file, "%s\n", current_word);
        word_count++;
        
        if (!next_word)
            break;
        
        next_word = nextWord(next_word, separators, current_word);
    };

    fclose(file);
    return word_count;
}

int str_includes(char* str, char* sub_str) {
    if (!str || !sub_str)
        return 0;

    while (*str && *sub_str) {
        // First letter does not match
        if (*str != *sub_str)
            return 0;
        
        str++;
        sub_str++;
    }

    return 1;
}

int countWordOccur(char* sentence, char* separators, char* query) {
    char* next_word = NULL;
    int occurences = 0;
    int max_length = strlen(sentence);

    char* current_word = (char*) malloc(sizeof(char) * max_length);
    if (!current_word) {
        fprintf(stderr, "Word buffer allocation failed");
        return -1;
    }

    do {
        next_word = nextWord(!next_word ? sentence : next_word, separators, current_word);
        occurences += str_includes(current_word, query);
    } while (next_word);

    return occurences;
}

/*
    Question 4 explanation:
    ****************************************
    Some tips for those kind of questions:
    - Examine the code from the main to the inner used functions.
    - Always use a side note to "watch" the variables on
    - In case of collision (two variables with same name but in other scopes, write down which variable you change)
    ****************************************
    
    As examining the code, you can see this program uses two kinds of variables.
    - Global variables
    - Function scoped variables

    Because of those two kinds of variables have the same naming, so it very confusing.
    Let's write down the variables.
 
    The initial values of the variables are:
    x = 30, y = 10
  
    > Main
    The main function is overwriting no varaibles, we will change the gloabl variables
    x = 30, y = 5
  
    executing `f1(20)`
        The funciton creates a variable with the same name of the global variable. 
        In this case the function creates new variable with the value of the function's argument.
      
        **From now on, let's call the overwritten values with leading _**
       _x = 20, y = 5
       print: x=20,y=5
       (The printed value is the overwritten value)
 
       _x = y = 10
       So we are changing the global y to the value 15, and the inner x (_x) to 10
 
    CHECKPOINT: The global variables values are: x = 30, y = 10

    executing `f2(y)`
        The function now "overwites" the value of y with the actual value of y. 
        but because it just copied into the variable, we will continue to call it `_y`

        x = 30, _y = 10
        print: x=30,y=10

        x = _y = 15;
    
    CHECKPOINT: The global variables values are: x=15, y=10
    print: x=15,y=10
 */

/*
    Question 5 explanation:
    
    A. (1).
    Because of the difference between `puts()` and `fputs()` is the file pointer, in the `puts()` function the file is the `stdout` file
    and in the `fputs()` it's configured manually. as far as the content concern, it will written the same to the output file.

    B. (6)
    All pointers are numrical addresses in the memory, so all the arithmetic operation are valid.
    The only concern with the pointers is the size of them. int takes more space in the memory hence can become larger than the max
    size of the pointer which is a risk of accessing an address that does not exists. Hence all the pointer-to-pointer, and int-to-pointer
    arithmetic operations are valid.
*/

/*
    Question 6 explanation:

    As discussed earlier in this implementation, the `puts` function is writing null-terminated ('\0') string into the stdout file
    Which usually printed in the console/terminal.
    
    Let's examine each of the operations step by step:
    1. String literals
        We can see multiple "" in this line, which represents a string literal.
        We also know that string literals are read-only and automatically null terminated.
    2. Arithmetic operations and strings
        When a string literal come across arithmetic operations the string will be considered as pointer to the first letter of the
        string. (which represents an numerical address)
        So we will continue to evaluate this as an arithmetic operation
    3. `strlen()` function
        As we know, the `strlen()` function counts the number characters (null-excluded) and returns `size_t` type (which is considered as number)
        So, we can evaluate now the return value of `strlen("strlen")`, which is 6, each letter is counted besides the null.
    4. `sizeof` operator
        The `sizeof` operator returns the bytes count of an address allocation in the memory (static and dynamic allocations) by pointer.
        So let's evaluate the `sizeof"sizeof"`.
        So it's string literal, which is considered as pointer to the first letter of the string. 
        Now the string "sizeof" is automatically null terminated, so it actually saved as ['s', 'i', 'z', 'e', 'o', 'f', '\0'].
        **Remember each char takes 1 byte.**
        Therefore this line will return the value 7.

    Let's call the first letter pointer of the first string literal: `fp`
    So the evaluation of the `puts` argument is: `*(fp-6+7)` which is actually `*(fp+1)`
    according to the change of the pointer the actual value will be "puts"+1 => "uts"
*/


/* Functions that have to be implemented to be able to run this code */

/**
 * Scans elements from the user and chaning them into linked list
 * @returns The newly created linked list
 */
Item* _scan_list() {
    Item* head = NULL;
    Item* tail = NULL;
    double coefficient_input;
    int power_input;

    puts("This is a function that construct a monom list.\n");
    do {
        printf("Enter the coefficient and power of X (format - coefficient<space>power) or 0 0 to stop: ");
        scanf("%lf%d", &coefficient_input, &power_input);

        Monom monom = { coefficient_input, power_input };
        Item* new_item = create_item(monom, NULL);

        if (!head) {
            tail = head = new_item;
        } else {
            tail->next = new_item;
            tail = new_item;
        }
    } while (coefficient_input || power_input);
    
    return head;
}

/**
 * Prints item list as mathematical equation in the format '2x^2-3x+2'
 * @param list The head of the list to print
 */
void _print_list(Item* list) {
    int first = 1;

    while (list) {
        if (list->mon.coefficient > 0 && list->mon.power && !first)
            printf("+%.1lfX^%d", list->mon.coefficient, list->mon.power);
        else if (list->mon.power)
            printf("%.1lfX^%d", list->mon.coefficient, list->mon.power);
        else
            printf(list->mon.coefficient < 0 ? "%.1lf" : "+%1.lf");

        list = list->next;
        first = 0;
    }

    printf("\n");
}

/* 
    Disclaimer: The focus of those implementations are in the intruction-based functions implementations
    All the memory managment in the prefix `_` and the main functions are intentionally ignored
    To write less code as possible where it not actually needed.
*/
int main() {
    int question_num;
    printf("Enter question number (1-3): ");
    scanf("%d", &question_num);

    switch (question_num) {
        case 1:
            Item* monoms_list = _scan_list();
            printf("Monom: ");
            _print_list(monoms_list);
            
            Item* polynom = createPolynom(monoms_list);
            printf("Polynom: ");
            _print_list(polynom);
            break;
        
        case 2:
            char filename[] = "output";
            char str[] = "a lot of words                in   Here";

            remove(filename);
            printf(!errno ? "Deleted last %s file\n" : "There was an error with deleting the file: %s\n", filename);
            
            int num_of_words = breakSentence(str, " ", filename);
            printf("Total words in output file: %d\n", num_of_words);
            break;

        case 3:
            char str2[] = "But why?! That's why. And don't ask me why.";
            int occurences = countWordOccur(str2, "? !.", "why");
            printf("Total occurences in test2: %d\n", occurences);
            break;

        default:
            printf("Unfamiliar question number entered, exiting.");
            break;
    }

    return 0;
}