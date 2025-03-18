#include <stdio.h>
#include <stdlib.h>

/*
    Typedef: 
        Is like type alias for the `c` language.
        The declaration is as follows: `typedef <Some type definition> <Alias/short name for it>;`
        For example: `typedef long long MyLong;` 
    
    Struct:
        Is the object block for passing multiple values within one return statement (like in or from a function).
        The declaration is as follows:
        ```
            struct <StructName> {
                <property type> property_name;
                <property type> another_property;
            };
        ```
        
        Definition example:
        ```
            struct Person {
                char name[30];
                int age;
            };
        ```

        In order to use it in the code you should state it as follows: `struct Person person_a;`
        But this kind of statements are bad practice in any language, so the advancment is better,
        it's more complex, but it easier to use across the code.

        Implementation like the follows.
*/
typedef struct Complex {
    double real;
    double img;
} Complex;

typedef struct Student {
    char name[30];
    int id_card;
    int grade;
} Student;

typedef struct Apartment {
    char address[30];
    int rooms;
    double price;
} Apartment;

/**
 * Generates a complex number by taking user input.
 * 
 * @param c Pointer to the Complex structure where the real and imaginary parts will be stored.
 * @return None.
 */
void gen_complex(Complex* c) {
    printf("Write the real parameter of the complex number: ");
    scanf("%lf", &c->real);
    printf("Write the img parameter of the complex number: ");
    scanf("%lf", &c->img);
}

/**
 * Prints a complex number in the standard format.
 * 
 * @param c Pointer to the Complex structure containing the real and imaginary parts.
 */
void print_complex(Complex* c) {
    if (!c->img) {
        printf("%f\n", c->real);
    } else {
        printf(c->img > 0 ? "%f+%fi\n" : "%f%fi\n", c->real, c->img);
    }
}

/**
 * Computes the sum of two complex numbers.
 * 
 * @param a Pointer to the first Complex number.
 * @param b Pointer to the second Complex number.
 * 
 * @return The sum of the two complex numbers.
 */
Complex sum_complex(Complex* a, Complex* b) {
    Complex sum;
    sum.real = a->real + b->real;
    sum.img = a->img + b->img;
    
    return sum;
}

/**
 * Computes the subtraction of two complex numbers.
 * 
 * @param a Pointer to the first Complex number.
 * @param b Pointer to the second Complex number.
 * 
 * @return The result of subtracting b from a.
 */
Complex sub_complex(Complex* a, Complex* b) {
    Complex substruction;
    substruction.real = a->real - b->real;
    substruction.img = a->img - b->img;
    
    return substruction;
}

/**
 * Computes the multiplication of two complex numbers.
 * 
 * @param a Pointer to the first Complex number.
 * @param b Pointer to the second Complex number.
 * 
 * @return The product of the two complex numbers.
 */
Complex multiply_complex(Complex* a, Complex* b) {
    Complex multiply;

    multiply.real = a->real * b->real - a->img * b->img;
    multiply.img = a->img * b->real + a->real * b->img;
    
    return multiply;
}

/**
 * Handles user input, arithmetic operations, and printing of complex numbers.
 * 
 * This function prompts the user to input two complex numbers, prints them, 
 * and then computes and displays their sum, subtraction, and multiplication results.
 */
void complex_number_handler() {
    struct Complex complex_num_1;
    gen_complex(&complex_num_1);
    
    printf("\n");
    struct Complex complex_num_2;
    gen_complex(&complex_num_2);
    
    printf("first number: ");
    print_complex(&complex_num_1);
    
    printf("second number: ");
    print_complex(&complex_num_2);
    
    printf("sum of these complex numbers: ");
    Complex sum = sum_complex(&complex_num_1, &complex_num_2);
    print_complex(&sum);
    
    printf("substruction of these complex numbers: ");
    Complex sub = sub_complex(&complex_num_1, &complex_num_2);
    print_complex(&sub);
    
    printf("multiplication of these complex numbers: ");
    Complex multi = multiply_complex(&complex_num_1, &complex_num_2);
    print_complex(&multi);
}

/**
 * Computes the average grade of an array of students.
 * 
 * @param students Pointer to an array of Student structures.
 * @param length The number of students in the array.
 * 
 * @return The average grade of the students.
 */
float get_avg(Student* students, int length) {
    int sum = 0;
    
    for (int i = 0; i < length; i++) {
        sum += students[i].grade;
    }
    
    return (float) sum / length;
}

/**
 * Counts and prints students based on their grades relative to the average.
 * 
 * This function prints the details of students whose grades are above or equal to the average 
 * and counts the number of students whose grades are below the average.
 * 
 * @param students Pointer to an array of Student structures.
 * @param length The number of students in the array.
 * @param avg The average grade used as a threshold.
 * 
 * @return The number of students whose grades are below the average.
 */
int get_below_avg(Student* students, int length, float avg) {
    int count_below_avg = 0;
    
    // Printing and returning the students above the avg and below the avg
    for (int i = 0; i < length; i++) {
        if (students[i].grade >= avg) {
            printf("Name: %s, ID: %d\n", students[i].name, students[i].id_card);
        } else {
            count_below_avg += 1;
        }
    }
    
    return count_below_avg;
}

/**
 * Computes the average grade of students and counts how many have grades below the average.
 * 
 * @param students Pointer to an array of Student structures.
 * @param length The number of students in the array.
 * @param avg Pointer to a float where the computed average grade will be stored.
 * 
 * @return The number of students whose grades are below the average.
 */
float students_stats(Student* students, int length, float* avg) {
    *avg = get_avg(students, length);
    int count_below_avg = get_below_avg(students, length, *avg);
    return count_below_avg;
}


/**
 * Manages student data, computes the class average, and identifies students below average.
 * 
 * This function initializes an array of students, calculates the class average, 
 * prints students with grades above or equal to the average, and displays the total 
 * count of students with grades below the average.
 */
void students_handler() {
    int length = 3;
    float avg;
    Student students[] = {
        { "Jhon", 0, 100 },
        { "Dan", 1, 100 },
        { "Cherry", 2, 90 }
    };
    
    int below_avg_count = students_stats(students, length, &avg);
    printf("Total students below avg: %d\n", below_avg_count);
    printf("Class avg: %lf", avg);
}

/**
 * Filters apartments based on the number of rooms and maximum price.
 * 
 * This function searches for apartments that match the specified number of rooms 
 * and have a price within the given budget. The filtered apartments are dynamically 
 * allocated and returned as a new array.
 * 
 * @param apartment_units Pointer to an array of Apartment structures.
 * @param length The total number of apartments in the input array.
 * @param target_rooms The desired number of rooms in the apartment.
 * @param max_price The maximum allowable price for the apartment.
 * @param new_length Pointer to an integer where the number of matched apartments will be stored.
 * 
 * @return A dynamically allocated array of Apartment structures that match the criteria.
 * Returns NULL if memory allocation fails.
 */
Apartment* filter_relevant_apartments(Apartment* apartment_units, int length, int target_rooms, int max_price, int* new_length) {
    int current_index = 0;
    Apartment* relevant_hits = (Apartment*) malloc(length * sizeof(Apartment));
    
    if (!relevant_hits)
        return NULL;
    
    for (int i = 0; i < length; i++) {
        if (apartment_units[i].rooms == target_rooms && apartment_units[i].price <= max_price)
            relevant_hits[current_index++] = apartment_units[i];
    }
    
    Apartment* reallocated_arr = (Apartment*) realloc(relevant_hits, current_index * sizeof(Apartment));
    
    printf("Current index: %d\n", current_index);
    *new_length = current_index;
    return reallocated_arr;
}

/**
 * Prints the details of an array of apartments.
 * 
 * This function iterates through the given array of apartments and prints their 
 * address, number of rooms, and price.
 * 
 * @param arr Pointer to an array of Apartment structures.
 * @param len The number of apartments in the array.
 */
void print_apartment_arr(Apartment* arr, int len) {
    for (int i = 0; i < len; i++)
        printf("Address: %s, Rooms: %d, Price: %f\n", arr[i].address, arr[i].rooms, arr[i].price);
}

/**
 * Handles apartment filtering and printing based on specified criteria.
 * 
 * This function initializes an array of apartments, filters them based on a target 
 * number of rooms and maximum price, prints the filtered apartments, and releases 
 * allocated memory.
 */
void apartment_handler() {
    Apartment apartment_units[] = {
        { "NYC Broorklyn", 5, 10000.0 },
        { "Another place", 20, 75000.0 },
        { "White house", 20, 5000000.0 },
        { "Chinatown 2412", 5, 2000.0 },
    };
    int length = 4;
    
    int filtered_arr_len;
    Apartment* filtered_arr = filter_relevant_apartments(apartment_units, length, 5, 100000, &filtered_arr_len);
    print_apartment_arr(filtered_arr, filtered_arr_len);
    
    free(filtered_arr);
}

int main() {
    complex_number_handler();
    printf("\n");
    students_handler();
    printf("\n");
    apartment_handler();
    
    return 0;
}