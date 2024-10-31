#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void print_environment_list() {
    extern char **environ;
    int i = 0;

    while (environ[i]) {
        printf("%s\n", environ[i]);
        i++;
    }
}

void print_environment_entry() {
    char *name = readline("Enter variable name: ");
    if (name == NULL) return;

    char *value = getenv(name);
    if (value) {
        printf("%s=%s\n", name, value);
    } else {
        printf("Environment variable '%s' not found.\n", name);
    }
    free(name);
}

void add_environment_entry() {
    char *name = readline("Enter variable name: ");
    char *value = readline("Enter variable value: ");
    if (name == NULL || value == NULL) return;

    if (setenv(name, value, 0) == 0) {
        printf("Added: %s=%s\n", name, value);
    } else {
        perror("Failed to add environment entry");
    }
    free(name);
    free(value);
}

void modify_environment_entry() {
    char *name = readline("Enter variable name: ");
    char *value = readline("Enter new variable value: ");
    if (name == NULL || value == NULL) return;

    if (setenv(name, value, 1) == 0) {
        printf("Modified: %s=%s\n", name, value);
    } else {
        perror("Failed to modify environment entry");
    }
    free(name);
    free(value);
}

void remove_environment_entry() {
    char *name = readline("Enter variable name: ");
    if (name == NULL) return;

    if (unsetenv(name) == 0) {
        printf("Removed environment variable '%s'.\n", name);
    } else {
        perror("Failed to remove environment entry");
    }
    free(name);
}

int main() {
    while (1) {
        puts("\n---------------------\n");
        puts("Environment-List Menu\n");
        puts("---------------------\n");
        puts("[1]: Print environment list\n");
        puts("[2]: Print environment entry\n");
        puts("[3]: Add environment entry\n");
        puts("[4]: Modify environment entry\n");
        puts("[5]: Remove environment entry\n");
        puts("[0]: End\n");

        char *choice = readline("Select an option: ");
        if (choice == NULL) break;

        int option = atoi(choice);
        free(choice);

        switch (option) {
            case 1:
                print_environment_list();
                break;
            case 2:
                print_environment_entry();
                break;
            case 3:
                add_environment_entry();
                break;
            case 4:
                modify_environment_entry();
                break;
            case 5:
                remove_environment_entry();
                break;
            case 0:
                puts("Exiting...\n");
                return 0;
            default:
                puts("Invalid option. Please try again.\n");
        }
    }
    return 0;
}
