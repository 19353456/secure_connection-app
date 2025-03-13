#include "utils.h"
#include <unistd.h>  // For crypt() - password hashing
#include <stdio.h>
#include <string.h>

int main() {
    char providers[10][3][12];
    char clients[10][3][12];

    int num_providers = load_from_file("providers.txt", providers);
    int num_clients = load_from_file("clients.txt", clients);

    int role;
    role = determine_role();
    printf("%d\n", role);

    char name[12];
    char pwd[12];
    char skill[12];
    char location[12];
    
    char new_password[12];
    char new_user_name[12];

    // Secure input for name
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);  // Safely read input
    name[strcspn(name, "\n")] = 0;  // Remove newline character if present

    // Secure input for password
    printf("Enter password: ");
    fgets(pwd, sizeof(pwd), stdin);  // Safely read input
    pwd[strcspn(pwd, "\n")] = 0;  // Remove newline character if present

    // Use crypt to hash the password (with a simple salt)
    char *salt = "$6$randomsalt$";  // Salt for SHA-512 hash
    char hashed_password[256];  // Adjust size to hold the hashed password
    strcpy(hashed_password, crypt(pwd, salt));  // Hash password

    // Example hardcoded role checks with crypt (for demonstration, you'd check against a stored hash)
    if (role == 1 && strcmp(hashed_password, crypt("cli123", salt)) == 0) {
        // Client role
        printf("Enter the skill you require: ");
        fgets(skill, sizeof(skill), stdin);  // Safely read input
        skill[strcspn(skill, "\n")] = 0;  // Remove newline character if present

        printf("Enter your location: ");
        fgets(location, sizeof(location), stdin);  // Safely read input
        location[strcspn(location, "\n")] = 0;  // Remove newline character if present

        printf("Here's a list of the providers in your location for the skills you require:\n");
        print_matches(providers, num_providers, skill, location);
    } else if (role == 2 && strcmp(hashed_password, crypt("pro456", salt)) == 0) {
        // Provider role
        printf("Enter the skill you provide: ");
        fgets(skill, sizeof(skill), stdin);  // Safely read input
        skill[strcspn(skill, "\n")] = 0;  // Remove newline character if present

        printf("Enter your location: ");
        fgets(location, sizeof(location), stdin);  // Safely read input
        location[strcspn(location, "\n")] = 0;  // Remove newline character if present

        printf("Here's a list of the clients in your location for the skills you provide:\n");
        print_matches(clients, num_clients, skill, location);
    } else {
        // Admin role
        printf("Welcome, administrator\n");

        // Secure input for new user creation
        printf("Enter name of user to create: ");
        fgets(new_user_name, sizeof(new_user_name), stdin);  // Safely read input
        new_user_name[strcspn(new_user_name, "\n")] = 0;  // Remove newline character if present

        printf("Enter password for that user: ");
        fgets(new_password, sizeof(new_password), stdin);  // Safely read input
        new_password[strcspn(new_password, "\n")] = 0;  // Remove newline character if present

        // Use crypt to hash the new user's password
        char hashed_new_password[256];
        strcpy(hashed_new_password, crypt(new_password, salt));  // Hash the new user's password

        printf("Creating new user with name: %s and hashed password: %s\n", new_user_name, hashed_new_password);
    }

    return 0;
}
