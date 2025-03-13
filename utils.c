#include "utils.h"
#include <stdio.h>
#include <string.h>

// Function to load data from a file (e.g., providers.txt or clients.txt)
int load_from_file(const char* filename, char table[10][3][12]) {
    FILE *fp = fopen(filename, "r");  // Open the file in read mode
    int rowi = 0;
    if (fp != NULL) {
        // Read lines from the file until the end
        while (!feof(fp)) {
            fscanf(fp, "%s %s %s", table[rowi][0], table[rowi][1], table[rowi][2]);
            rowi++;  // Increment row index
        }
        fclose(fp);  // Close the file after reading
    }
    return rowi;  // Return the number of rows read
}

// Function to determine user role (client, provider, or admin)
int determine_role() {
    int role;
    printf("Enter your role: 1 for client, 2 for provider, 3 for admin: ");
    scanf("%d", &role);  // Read the user's role choice
    return role;  // Return the user's role
}

// Function to print matching results from the table based on skill and location
void print_matches(char table[10][3][12], int rows, const char* skill, const char* location) {
    for (int i = 0; i < rows; i++) {
        // Compare skill and location; print if there is a match
        if (strcmp(table[i][1], skill) == 0 && strcmp(table[i][2], location) == 0) {
            printf("%s\n", table[i][0]);  // Print the matched name (client/provider)
        }
    }
}

// Function to display all entries in the table (clients or providers)
void show_all(char table[10][3][12], int rows) {
    if (rows != 0) {
        for (int i = 0; i < rows; i++) {
            // Print all details (name, skill, location) for each entry
            printf("%d : %s %s %s\n", i, table[i][0], table[i][1], table[i][2]);
        }
    } else {
        // Print a message if the table is empty
        printf("-- empty table --\n");
    }
}
