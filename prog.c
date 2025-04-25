#include <stdio.h>
#include <string.h>

int main() {
    // Increased buffer size
    char name[64] = "";
    char password[64] = "";

    // Prompt user to enter their name
    printf("Enter your name: ");
    if (fgets(name, sizeof(name), stdin) != NULL) {
        // Remove newline character if it's present
        name[strcspn(name, "\n")] = '\0';  // Clean up input
    }

    // Prompt user to enter their password
    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character if it's present
        password[strcspn(password, "\n")] = '\0';  // Clean up input
    }

    // Displaying the entered values (just for testing)
    if (name != NULL) {
        printf("Name: %s\n", name);
    }
    if (password != NULL) {
        printf("Password: %s\n", password);
    }

    return 0;
}
