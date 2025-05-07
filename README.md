Advanced programming course HIT:

In this course we discuss more advanced aspects in the broader programming, such as: `Linked List` vs. `Array List` and `2d array` (matrix) structures, and `c` challenges such as linked list deallocation.

## Elaboration:
Here is a list of links that gives some elaboration about the course's subjects: <br/>
- [ArrayList vs. Linked List](https://www.youtube.com/watch?v=xFMXIgvlgcY)

## Requirements:
- GCC

## Repository structure:
```
/---repository_root
|   black_box.c - "black box functions" that can be used in this course without implementation.
|
/---.vscode/ - Visual studio code configurations file in order to build and debug this repository in visual studio code .
|
/---assignments - The assignments given in this course, the folder sturcture single directory for the `instructions`, all the folders that named by number contains the actual assignemnt. which may vary its contents due to the specific instructions of each assignemnt.
|   /---1
|   |       assignment.c
|   |
|   /---instructions - This folder contains all the instructions/questions files that regarding the specific assignment
|           assignment_1.pdf
|
/---class_works - The class works given during this course, all of the implementation files are gathered together at this folder. all the instructions are placed in the `instructions` sub-folder. The instructions files and `.c` files are corresponding one another for easy navigaion in this repository.
    |   class_work_2.c
    |   ...
    |
    /---instructions
        |    class_work_2.pdf
        |    ...
```
## Naming conventions "best practices" for `c`:
This file has all the naming convenstions you may across during reading the code in this repository.
These naming convensions considerd as *"best practice"*. 
```c
// File: my_module.c              // file names: lowercase_with_underscores.c/.h

#ifndef MY_MODULE_H               // macro_names: ALL_CAPS_WITH_UNDERSCORES, prefixed by file/module
#define MY_MODULE_H

#include <stdio.h>

// Macro constant: ALL_CAPS_WITH_UNDERSCORES
#define MAX_BUFFER_SIZE 1024

// Global variable: snake_case with 'g_' prefix
int g_connection_count = 0;

// Constant variable (const): snake_case (macros SHOULD be ALL_CAPS)
const int default_timeout = 30;

// Type name (typedef): PascalCase (avoid _t suffix)
typedef struct {
    int id;
    char name[256];
} UserProfile;

// Struct tag: snake_case
struct user_profile {
    int id;
    char name[256];
};

// Enum constants: ALL_CAPS_WITH_UNDERSCORES, prefixed to namespace
typedef enum {
    USER_STATUS_ACTIVE,
    USER_STATUS_INACTIVE,
    USER_STATUS_BANNED
} UserStatus;

// Function name: snake_case, use verb or verb_noun patterns
void initialize_user_profile(UserProfile *profile) {
    profile->id = 0;
    profile->name[0] = '/0';
}

// Another function example
int calculate_retry_delay(int attempt_number) {
    // Local variable: snake_case
    int delay = attempt_number * default_timeout;
    return delay;
}

int main(void) {
    // Local variable in snake_case
    char user_name_buffer[MAX_BUFFER_SIZE];

    // Avoid reserved identifiers (do NOT use):
    // int _myVar;      // invalid: leading underscore
    // int __another;   // invalid: double underscore
    
    UserProfile user;                   // using PascalCase type
    initialize_user_profile(&user);     // calling snake_case function
    int wait = calculate_retry_delay(3);
    
    printf("Connection count: %d/n", g_connection_count);
    printf("Calculated delay: %d seconds/n", wait);
    
    return 0;
}

#endif // MY_MODULE_H
```