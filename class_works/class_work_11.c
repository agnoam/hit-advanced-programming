#include <stdio.h>
#include <stdlib.h>
#include "../black_box.c"


void write_file_if_not_exists(char* filename) {
    FILE *target = fopen(filename, "r");
    
    // File exists and should be left as-is
    if (target) 
        return;

    printf("Writing the file because it does not exists\n");
    target = fopen(filename, "w");
    fprintf(target, "%s", "A a a z\n");
    fprintf(target, "%s", "b B B Z\n");
    fprintf(target, "%s", "C C C z");
    
    fclose(target);
}


int count_lines(char *filename) {
    int line_count = 1;
    FILE* file = fopen(filename, "r");
    if (!file)
        return -1;

    char current_char = getc(file);
    while (current_char != EOF) {
        if (current_char == '\n')
            line_count++;
        current_char = getc(file);
    }

    fclose(file);
    return line_count;
}


void letter_frequency(char *filename, int counts[26]) {
    // Resetting the array
    for (int i = 0; i < 26; i++)
        counts[i] = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("File does not exists");
        return;
    }

    for (char current_char = getc(file); current_char != EOF; current_char = getc(file)) {
        if (current_char >= 'a' && current_char <= 'z')
            counts[current_char - 'a']++;
        else if (current_char >= 'A' && current_char <= 'Z')
            counts[current_char - 'A']++;
    }

    fclose(file);
}


void remove_spaces(char *infile, char *outfile) {
    FILE *input_file = fopen(infile, "r");
    FILE *output_file = fopen(outfile, "w");

    if (!input_file || !output_file) {
        perror("One or both of the file are unavailable");
        return;
    }

    for (char current_char = getc(input_file); current_char != EOF; current_char = getc(input_file)) {
        if (current_char != ' ')
            fprintf(output_file, "%c", current_char);
    }

    fclose(input_file);
    fclose(output_file);
}


int main() {
    char* filename = "testfile.dump";
    char* output_filename = "output.dump";
    int counts[26] = { 0 };

    // File initialization
    write_file_if_not_exists(filename);

    printf("Lines in file: %d\n", count_lines(filename));
    printf("The letters in the file are (each position means the letter index \"a/A\" will be at index 0 \"z/Z\" will 25): \n");
    letter_frequency(filename, counts);
    print_array(counts, 26);
    remove_spaces(filename, output_filename);
    printf("Check out %s", output_filename);

    return 0;
}