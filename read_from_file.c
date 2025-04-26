#include <stdio.h>

void write_to_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "a");  // Open file for appending
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s\n", content);  // Write content to file
    fclose(file);
}

void read_from_file(const char *filename) {
    char buffer[256];
    FILE *file = fopen(filename, "r");  // Open file for reading
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);  // Print each line
    }
    fclose(file);
}

int main() {
    const char *filename = "providers.txt";  // File to write to

    // Write to the file
    write_to_file(filename, "New Provider");

    // Read from the file to verify
    read_from_file(filename);

    return 0;
}
