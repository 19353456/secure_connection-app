
#include "utils.h"
int determine_role () {

    int role;
    printf("What is your role: \n");
    printf("1. client \n");
    printf("2. provider\n");
    printf("3. admin\n");
    printf("Enter role: ");
    scanf("%d", &role);
    return role;

}

int load_from_file(const char* filename, char table[10][3][12]) {
    char line[32];
    FILE *fp = fopen(filename, "r");
    int rowi = 0;
    if (fp != NULL) {
        while (!feof(fp)) {
            int n1 = fscanf(fp, "%s", table[rowi][0]);
            int n2 = fscanf(fp, "%s", table[rowi][1]);
            int n3 = fscanf(fp, "%s", table[rowi][2]);
            if ((n1 != -1) && (n2 != -1) && (n3!=-1)) {
                rowi++;
            }

        }

    }
    return rowi;

}

void print_matches(char table[10][3][12], int rows, const char* skill, const char* location) {
    for (int i = 0; i < rows; i++) {
        if ((strcmp(table[i][1], skill) == 0) && (strcmp(table[i][2], location) == 0)){
            printf("%s\n", table[i][0]);
        }
    }
}

void show_all(char table[10][3][12], int rows) {
    if (rows != 0) {
        for (int i = 0; i < rows; i++) {
            printf("%d : %s %s %s\n", i, table[i][0], table[i][1], table[i][2]);
        }
    } else {
        printf("-- empty table --\n");
    }

}

