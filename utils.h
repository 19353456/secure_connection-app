#ifndef UTILS_H
#define UTILS_H

// Function declarations
int determine_role();
int load_from_file(const char* filename, char table[10][3][12]);
void print_matches(char table[10][3][12], int rows, const char* skill, const char* location);
void show_all(char table[10][3][12], int rows);

#endif  // UTILS_H
