
#include "utils.h"




int main() {

    char providers[10][3][12];
    char clients[10][3][12];

    int num_providers = load_from_file("providers.txt", providers);
    int num_clients = load_from_file("clients.txt", clients);

    int role;
    role = determine_role();
    printf("%d\n ", role);

    char name[12];
    char pwd[12];
    char skill[12];
    char location[12];
    
    char new_password[12];
    char new_user_name[12];

    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", pwd);

    if ((role ==1 ) && (strcmp(pwd,"cli123")==0)) {
        printf("Enter the skill you require: ");
        scanf("%s", skill);
        printf("Enter your location: ");
        scanf("%s", location);
        
        printf("Here's a list of the providers in your location for the skills you require: \n");
        print_matches(providers, num_providers, skill, location);
    } else if ((role ==2 ) && (strcmp(pwd,"pro456")==0)) {
        printf("Enter the skill you provide: ");
        scanf("%s", skill);
        printf("Enter your location: ");
        scanf("%s", location);

        printf("Here's a list of the clients in your location for the skills you provide: \n");
        print_matches(clients, num_clients, skill, location);
    } else {
        printf("Welcome, administrator\n");
        printf("Enter name of user to create: \n");
        scanf("%s", new_user_name);
        printf("Enter password for that user: \n");
        scanf("%s", new_password);
        printf("Creating new user with name ");
        printf("%s", new_user_name);
        printf(" and password ");
        printf("%s", new_password);
        printf("\n");

    }

    return 0;

}
