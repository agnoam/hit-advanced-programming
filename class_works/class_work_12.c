#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Anonymous struct
typedef struct {
    // Adding 1 extra for indcluding the \0 at the end
    char id[10]; // Originally 9
    char name[31]; // Originally 30
    double cart;
} CartRecord;

CartRecord new_cart(char id[], char name[], double cart) {
    int i = 0;
    CartRecord new_cart;

    // Hard copying the strings into the new struct
    for (i = 0; i < 9; i++)
        new_cart.id[i] = id[i];
    new_cart.id[i] = '\0'; // Putting trailing \0

    for (i = 0; i < 30; i++)
        new_cart.name[i] = name[i];
    new_cart.name[i] = '\0'; // Putting trailing \0

    new_cart.cart = cart;
    return new_cart;
}

void create_file(CartRecord record, char* filename, int is_binary) {
    FILE* file = fopen(filename, is_binary ? "ab" : "a");
    if (!file) {
        perror("Can not write to the file");
        return;
    }

    (is_binary) ? fwrite(&record, sizeof(CartRecord), 1, file) : fprintf(file, "%9s %30s %8.2lf\n", record.id, record.name, record.cart);
    fclose(file);
}

int update_file(char id[], int cart_sum, char* filename) {
    int elements_num = 0, return_value = 0;
    const long RECORD_SIZE = (long) sizeof(CartRecord);
    CartRecord* record = (CartRecord*) calloc(1, RECORD_SIZE);
    
    /* 
        The difference between `rb+` and `wb+` is the logic when the file is not exists:
        `rb+`: Returns `NULL` pointer
        `wb+`: Creates file
    */
    FILE *file = fopen(filename, "rb+");
    if (!file)
        return 0;

    do {
        if (!strcmp(record->id, id)) {
            CartRecord updated_row = new_cart(id, record->name, record->cart + cart_sum);
            
            // Seeking back from the current place in the file to replace the current record
            fseek(file, -RECORD_SIZE, SEEK_CUR);
            fwrite(&updated_row, RECORD_SIZE, 1, file);
            return_value = 1;
            break;
        }

        elements_num = fread(record, RECORD_SIZE, 1, file);
    } while(elements_num);

    fclose(file);
    return return_value;
}

char* read_line(FILE* file, int line_max_chars) {
    char current_char;
    int i = 0;
    char* buffer = (char*) calloc(line_max_chars, sizeof(char));
    
    do {
        current_char = getc(file);
        buffer[i++] = current_char;
    } while(current_char != EOF && current_char != '\n');

    return buffer;
}

void read_txt_file(char* filename) {
    const int LINE_CHAR_LENGTH = 10+31+10;
    FILE* file = fopen(filename, "r+");
    if (!file)
        return;

    char* current_line = NULL;
    do {
        if (current_line) {
            printf("%s", current_line);
            free(current_line);
        }
        
        current_line = read_line(file, LINE_CHAR_LENGTH);
    } while (!feof(file));
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

    printf("Is file updated ? %d\n", update_file("134679258", 320, filename_bin));
    printf("And now? %d", update_file("234567891", 456, filename_bin));

    printf("File contents:\n");
    read_txt_file(filename_txt);
    return 0;
}
