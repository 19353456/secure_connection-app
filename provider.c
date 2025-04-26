#include <stdio.h>
#include <string.h>
#include <bcrypt.h>

int main() {
    char provider_name[64];
    char password[64];
    char hashed_password[128];
    char salt[BCRYPT_HASHSIZE];  // Buffer to store the salt

    // Prompt user for provider details
    printf("Enter provider name: ");
    fgets(provider_name, sizeof(provider_name), stdin);
    provider_name[strcspn(provider_name, "\n")] = '\0';  // Remove newline

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline

    // Generate salt
    if (bcrypt_gensalt(12, salt) != 0) {
        fprintf(stderr, "Error generating salt\n");
        return 1;
    }

    // Hash the password with the generated salt
    if (bcrypt_hashpw(password, salt, hashed_password) != 0) {
        fprintf(stderr, "Error hashing password\n");
        return 1;
    }

    // Open the file for appending
    FILE *file = fopen("providers.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write provider info to file
    fprintf(file, "%s,%s\n", provider_name, hashed_password);
    fclose(file);

    printf("New provider added: %s\n", provider_name);
    return 0;
}
