#include "utils.h"
#include <stdio.h>
#include <string.h>

int determine_role() {
    int role;
    printf("What is your role: \n1. Client\n2. Provider\n3. Admin\nEnter role: ");
    if (scanf("%d", &role) != 1) {
        printf("Invalid input. Defaulting to Admin.\n");
        role = 3;  // Default to Admin if input is invalid
    }
    while (getchar() != '\n'); // Clear input buffer
    return role;
}

int load_from_file(const char* filename, char table[10][3][12]) {
    FILE *fp = fopen(filename, "r");
    int rowi = 0;
    if (fp != NULL) {
        while (rowi < 10 && fscanf(fp, "%11s %11s %11s", 
                  table[rowi][0], table[rowi][1], table[rowi][2]) == 3) {
            rowi++;
        }
        fclose(fp);
    } else {
        printf("Error: Could not open file %s\n", filename);
    }
    return rowi;
}

void print_matches(char table[10][3][12], int rows, const char* skill, const char* location) {
    int found = 0;
    for (int i = 0; i < rows; i++) {
        if ((strcmp(table[i][1], skill) == 0) && (strcmp(table[i][2], location) == 0)) { 
            printf("%s\n", table[i][0]);
            found = 1;
        }
    }
    if (!found) {
        printf("No matches found.\n");
    }
}

void show_all(char table[10][3][12], int rows) {
    if (rows > 0) {
        for (int i = 0; i < rows; i++) {
            printf("%d: %s %s %s\n", i, table[i][0], table[i][1], table[i][2]);
        }
    } else {
        printf("-- Empty table --\n");
    }
}
