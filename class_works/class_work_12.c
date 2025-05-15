#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_LENGTH 9
#define NAME_LENGTH 30
#define TEXT_LINE_LENGTH (ID_LENGTH + NAME_LENGTH + 10 + 3)

// Anonymous struct
typedef struct {
    char id[ID_LENGTH + 1];
    char name[NAME_LENGTH + 1];
    double cart;
} CartRecord;

/**
 * This function creates a new cart record with the given `ID`, `name`, and `cart` value.
 * 
 * @param id The ID of the new cart record.
 * @param name The name of the new cart record.
 * @param cart The cart value of the new cart record.
 * 
 * @return The new cart record. If the `ID` or `name` is not provided, an empty cart record is returned.
 */
CartRecord new_cart(char id[], char name[], double cart) {
    int i = 0;
    CartRecord new_cart;

    if (!id || !name) {
        perror("ID or name is not provided");
        CartRecord empty = { "", "", 0 };
        return empty;
    }
    
    new_cart.cart = cart;
    strncpy(new_cart.id, id, ID_LENGTH);
    strncpy(new_cart.name, name, NAME_LENGTH);
    
    // Adding trailing '\0' in the last character in both of the strings
    new_cart.id[ID_LENGTH] = '\0'; // Putting trailing \0
    new_cart.name[NAME_LENGTH] = '\0'; // Putting trailing \0

    return new_cart;
}

/**
 * This function creates a file and writes a record into it. The record can be written in binary or text format.
 * 
 * @param record The record to write into the file.
 * @param filename The name of the file to create.
 * @param is_binary A flag indicating whether the file is binary or not.
 */
void create_file(CartRecord record, char* filename, int is_binary) {
    FILE* file = fopen(filename, is_binary ? "ab" : "a");
    if (!file) {
        perror("Can not write to the file");
        return;
    }

    (is_binary) ? fwrite(&record, sizeof(CartRecord), 1, file) : fprintf(file, "%9s %30s %8.2lf\n", record.id, record.name, record.cart);
    fclose(file);
}

/**
 * This function updates a record in a file. If the file is binary, it seeks the record and overwrites it.
 * If the file is text, it creates a temporary file, writes the updated records into it, and then copies it back to the original file.
 * 
 * @param id The ID of the record to update.
 * @param cart_sum The new cart sum to update.
 * @param filename The name of the file to update.
 * @param is_binary A flag indicating whether the file is binary or not.
 *  
 * @return 1 if the record was updated successfully, 0 otherwise.
 */
int update_file(char id[], int cart_sum, char* filename, int is_binary) {
    int elements_num = 0, return_value = 0;
    const long RECORD_SIZE = (long) sizeof(CartRecord);
    CartRecord* record = (CartRecord*) calloc(1, RECORD_SIZE);
    
    /* 
        The difference between `rb+` and `wb+` is the logic when the file is not exists:
        `rb+`: Returns `NULL` pointer
        `wb+`: Creates file
    */
    FILE *file = fopen(filename, is_binary ? "rb+" : "r+");
    if (!file)
        return 0;

    if (is_binary) {
        do {
            if (!strcmp(record->id, id)) {
                CartRecord updated_row = new_cart(id, record->name, record->cart + cart_sum);
                
                // Seek back to the beginning of the current record and overwrite it
                fseek(file, -RECORD_SIZE, SEEK_CUR);
                fwrite(&updated_row, RECORD_SIZE, 1, file);
                return_value = 1;
                break;
            }

            elements_num = fread(record, RECORD_SIZE, 1, file);
        } while(elements_num);
    } else {
        /* 
            In text file the system can not seek the pointer in the file such as binary files.
            So we will have to duplicate the contents of the file into a temporary file and write our updated row instead.
            
            After that we will copy line by line the temp file into the original file.
        */
        FILE *temp = tmpfile();
        char line[TEXT_LINE_LENGTH];
        
        // Read each line from the original file
        while (fgets(line, sizeof(line), file)) {
            // Parse the line into a `CartRecord` struct by sacnning the line using this format
            sscanf(line, "%9s %30s %lf", record->id, record->name, &record->cart);
            
            if (!strcmp(record->id, id)) {
                record->cart += cart_sum;
                return_value = 1;
            }

            // Write the same or the updated row into the temp file
            fprintf(temp, "%9s %30s %8.2lf\n", record->id, record->name, record->cart);
        }

        // Rewind the temporary file to the beginning
        rewind(temp);
        file = freopen(filename, "w", file); // Reopen the original file in write mode to overwrite it
        
        // Write the contents of the temporary file to the original file
        while (fgets(line, sizeof(line), temp))
            fputs(line, file);
        
        fclose(temp);
    }

    // Close the original file
    fclose(file);
    return return_value;
}

/**
 * Printing text file line by line
 * 
 * @param filename Target file to print
 */
void print_txt_file(char* filename) {
    char current_line[TEXT_LINE_LENGTH];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File not exists or can not open it");
        return;
    }
    
    while (fgets(current_line, TEXT_LINE_LENGTH, file))
        printf("%s", current_line);
}

int main() {
    char* filename_bin = "test_name.bin";
    char* filename_txt = "test_name.txt";

    if (!fopen(filename_bin, "r")) {
        create_file(new_cart("123456789", "Test", 123), filename_bin, 1);
        create_file(new_cart("234567891", "BBB", 234), filename_bin, 1);
    }

    if (!fopen(filename_txt, "r")) {
        create_file(new_cart("123456789", "Test", 123), filename_txt, 0);
        create_file(new_cart("234567891", "BBB", 234), filename_txt, 0);
    }

    printf("Is file updated ? %d\n", update_file("134679258", 320, filename_bin, 1));
    printf("And now? %d", update_file("234567891", 456, filename_bin, 1));
    
    printf("Is file updated ? %d\n", update_file("134679258", 320, filename_txt, 0));
    printf("And now? %d", update_file("234567891", 456, filename_txt, 0));

    printf("File contents:\n");
    print_txt_file(filename_txt);
    return 0;
}
