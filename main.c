#include <stdio.h>
#include <stdlib.h>

// Declare functions from other files
int login();
void sign_up();
void payrollMenu();
void add_employee();
void view_employee();
void update_employee();
void delete_employee();

void employeeMenu() {
    int choice;
    do {
        printf("\n==== Employee Management Menu ====\n");
        printf("1. Add Employee\n");
        printf("2. View Employee\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_employee(); break;
            case 2: view_employee(); break;
            case 3: update_employee(); break;
            case 4: delete_employee(); break;
            case 0: break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);
}

int main() {
    int choice, loggedIn = 0;

    do {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Sign Up\n");
        printf("2. Login\n");
        printf("3. Employee Management\n");
        printf("4. Payroll System\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sign_up();
                break;
            case 2:
                loggedIn = login();
                break;
            case 3:
                if (loggedIn)
                    employeeMenu();
                else
                    printf("Please login first!\n");
                break;
            case 4:
                if (loggedIn)
                    payrollMenu();
                else
                    printf("Please login first!\n");
                break;
            case 0:
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
