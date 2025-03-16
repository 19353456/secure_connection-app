#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include "utils.h"

int main() {
    char providers[10][3][12] = {{0}};
    char clients[10][3][12] = {{0}};

    int num_providers = load_from_file("providers.txt", providers);
    int num_clients = load_from_file("clients.txt", clients);

    int role = determine_role();
    printf("%d\n", role);

    char name[12] = {0};
    char pwd[12] = {0};
    char skill[12] = {0};
    char location[12] = {0};
    char new_password[12] = {0};
    char new_user_name[12] = {0};

    printf("Enter name: ");
    if (fgets(name, sizeof(name), stdin) != NULL) {
        name[strcspn(name, "\n")] = '\0';  // Remove newline
    }

    printf("Enter password: ");
    if (fgets(pwd, sizeof(pwd), stdin) != NULL) {
        pwd[strcspn(pwd, "\n")] = '\0';
    }

    if ((role == 1) && (strcmp(pwd, "cli123") == 0)) {
        printf("Enter the skill you require: ");
        if (fgets(skill, sizeof(skill), stdin) != NULL) {
            skill[strcspn(skill, "\n")] = '\0';
        }

        printf("Enter your location: ");
        if (fgets(location, sizeof(location), stdin) != NULL) {
            location[strcspn(location, "\n")] = '\0';
        }

        printf("Here's a list of providers in your location for the skills you require:\n");
        print_matches(providers, num_providers, skill, location);
    } else if ((role == 2) && (strcmp(pwd, "pro456") == 0)) {
        printf("Enter the skill you provide: ");
        if (fgets(skill, sizeof(skill), stdin) != NULL) {
            skill[strcspn(skill, "\n")] = '\0';
        }

        printf("Enter your location: ");
        if (fgets(location, sizeof(location), stdin) != NULL) {
            location[strcspn(location, "\n")] = '\0';
        }

        printf("Here's a list of clients in your location for the skills you provide:\n");
        print_matches(clients, num_clients, skill, location);
    } else {
        printf("Welcome, administrator\n");
        printf("Enter name of user to create: ");
        if (fgets(new_user_name, sizeof(new_user_name), stdin) != NULL) {
            new_user_name[strcspn(new_user_name, "\n")] = '\0';
        }

        printf("Enter password for that user: ");
        if (fgets(new_password, sizeof(new_password), stdin) != NULL) {
            new_password[strcspn(new_password, "\n")] = '\0';
        }

        printf("Creating new user with name: %s and password: %s\n", new_user_name, new_password);
    }

    return 0;
}
