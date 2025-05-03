#include <stdio.h>
#include <string.h>

#define USER_FILE "D:\\pi\\80\\users.txt"

// Helper to remove newline from strings
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// SIGN UP FUNCTION
void sign_up() {
    int user_id;
    char password[50], confirm_password[50];

    printf("\n--- SIGN UP ---\n");
    printf("Enter new User ID: ");
    scanf("%d", &user_id);
    getchar(); // flush newline

    printf("Create Password: ");
    fgets(password, sizeof(password), stdin);
    remove_newline(password);

    int attempts = 2;
    do {
        printf("Confirm Password: ");
        fgets(confirm_password, sizeof(confirm_password), stdin);
        remove_newline(confirm_password);

        if (strcmp(password, confirm_password) != 0) {
            printf("Passwords do not match. Try again.\n");
        } else {
            FILE *fp = fopen(USER_FILE, "a");
            if (fp == NULL) {
                printf("Error opening user file.\n");
                return;
            }
            fprintf(fp, "%d %s\n", user_id, password);
            fclose(fp);
            printf("Sign-up successful!\n");
            break;
        }
    } while (--attempts >= 0);
}

// VALIDATE USER FUNCTION
int validate_user(int user_id, char password[]) {
    FILE *fp = fopen(USER_FILE, "r");
    int file_user_id;
    char file_password[50];

    if (fp == NULL) {
        printf("User file not found.\n");
        return 0;
    }

    while (fscanf(fp, "%d %s", &file_user_id, file_password) != EOF) {
        if (user_id == file_user_id && strcmp(password, file_password) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// LOGIN FUNCTION
int login() {
    int user_id;
    char password[50];

    printf("\n--- LOGIN ---\n");
    printf("User ID: ");
    scanf("%d", &user_id);
    getchar(); // flush newline

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    remove_newline(password);

    if (validate_user(user_id, password)) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Invalid credentials.\n");
        return 0;
    }
}
