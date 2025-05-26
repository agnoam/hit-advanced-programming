#include <stdio.h>
#include <stdlib.h>

/*
    Enum elaboration:
    Enum is a fixed set of distinct values with distinct variable names (properties)
    Each property represents an integer value, which can be defined by the user, or can be defined automatically.
    (in case the values defined automatically the first value will be 0)
    
    In the example below the first value is manually defined, and then it will increase by one at each new property
    automatically.
*/

typedef enum {
    CHAR = 1, // Starting from 1
    INT, // Automatically set to 2
    DOUBLE // 3, etc.
} SelectorType;

/*
    Union elaboration: 
    Union is a special type of type declaration which resmble to `struct` declaration but
    have some key differences.

    Union is "multi type" variable, which can store just one value in the same time.
    The union has a special sizing mechanism that will always allocate the "worst case" space.
    For example:
        The union is:
        ```
        union test {
            char arr[30];
            int number;
        };
        ```

        and we will run the commands:
        ```
        union test a;
        a.number = 1;
        printf("%d", sizeof(a));
        ```

        The expected output will be:
        > 32

        Even though `a` does not have `test.arr` initialized and the size of an int is `4`.
        C will choose to allocate the worst-case scenario for the single variable it holds up.
        (In our case 32. which is the sum of `30` bytes for the array, and some padding most of the time will be minor)

        Disclamer: The explnation of the the memory alignment and padding is simplified, for more accurate description
        read about "memory alignment and padding in c" (It's outside of the course scope)
*/

union one_of_three {
    char char_val;
    int int_val;
    double double_val;
};

typedef struct three_type {
    union one_of_three value;
    int selector;
} ThreeType;

/**
 * Scans input based on a specified type and stores it in a `ThreeType` union.
 *
 * This function prompts the user to enter a value, the type of which is determined
 * by `type_to_scan`. The input is then read using `scanf` and stored in the
 * appropriate member of the `value` union within the `ThreeType` structure
 * pointed to by `ptr`. The `selector` member of `ptr` is also set to
 * reflect the scanned type.
 *
 * @param type_to_scan An integer representing the type of data to scan.
 * It should correspond to one of the `SelectorType` enum values
 * (e.g., `CHAR`, `INT`, `DOUBLE`).
 * @param ptr A pointer to a `ThreeType` union where the scanned value will be stored.
 */
void scan_three(int type_to_scan, ThreeType *ptr) {
    ptr->selector = (SelectorType) type_to_scan;
    switch ((SelectorType) type_to_scan) {
        case CHAR:
            char char_input;
            
            printf("Enter char to save: ");
            scanf("%c", &ptr->value.char_val);
            break;

        case INT:
            int int_input;

            printf("Enter number to save: ");
            scanf("%d", &int_input);
            ptr->value.int_val = int_input;
            break;

        case DOUBLE:
            double double_input;

            printf("Enter decimal number to save: ");
            scanf("%lf", &double_input);
            ptr->value.double_val = double_input;
            break;
    }
}

/**
 * Prints the value and type of a `ThreeType` variable.
 *
 * This function takes a `ThreeType` union as input and prints its stored
 * value along with its `selector` type. The output format adapts based on
 * whether the stored value is an integer, double, or character.
 *
 * @param variable The `ThreeType` variable to be printed.
 */
void print_three(ThreeType variable) {
    printf("ThreeType: (");
    switch (variable.selector) {
        case INT:
            printf("value: %d, type: %d)\n", variable.value, variable.selector);
            break;
            
        case DOUBLE:
            printf("value: %lf, type: %d)\n", variable.value, variable.selector);
            break;
            
        case CHAR:
            printf("value: %c, type: %d)\n", variable.value, variable.selector);
            break;
    }
}

/**
 * Statful function which prints the console "Third time lucky" every 3rd time of exection
 */
void print_lucky() {
    /* 
        Static variable elaboration: 
        Static variable is a special variable attribute, which can be assigned to any type of variable.
        The attribute will retain it's value as long as the program still running. The variable will be accessible
        just in this function (a.k.a. the function's scope).

        In this implementaion, the `lucky_counter` will retain it's value each function call. 
        and will increase each function call. 
        In the professional jargon it called "stateful function". 
        which means that function handles memory of it's own, and can provide another value due to the change of the
        "state" - internal variables it's own and persist across the function's call invokes.
    */
    
    static int lucky_counter = 1;
    if (!(lucky_counter % 3)) 
        printf("Third time lucky (%d)\n", lucky_counter);

    lucky_counter++;
}

int main() {
    ThreeType variable;
    int type;

    printf("What type to scan (1 - char, 2 - int, 3 - double): ");
    scanf("%d", &type);
    scan_three(type, &variable);
    print_three(variable);
    
    for (int i = 0; i < 10; i++)
        print_lucky();

    return 0;
}