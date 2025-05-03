#include <stdio.h>
#include <string.h>

// Structure to store employee data
typedef struct {
    int emp_id;
    char name[100];
    int age;
    float salary;
} Employee;

#define FILE_NAME "D:\\pi\\80\\employee_data.txt"

// Function to add a new employee
void add_employee() {
    Employee emp;
    
    printf("\n--- ADD EMPLOYEE ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &emp.emp_id);
    getchar(); // To consume the newline character left by scanf

    printf("Enter Employee Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0';  // Remove trailing newline character

    printf("Enter Employee Age: ");
    scanf("%d", &emp.age);

    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    // Open the file in append mode to add the new employee
    FILE *fp = fopen(FILE_NAME, "a");
    if (fp == NULL) {
        printf("Error opening employee data file.\n");
        return;
    }

    // Save the employee data into the file
    fprintf(fp, "%d %s %d %.2f\n", emp.emp_id, emp.name, emp.age, emp.salary);
    fclose(fp);

    printf("Employee added successfully!\n");
}

// Function to view employee details by ID
void view_employee() {
    int emp_id;
    int found = 0;
    Employee emp;

    printf("\n--- VIEW EMPLOYEE ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &emp_id);

    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening employee data file.\n");
        return;
    }

    while (fscanf(fp, "%d %s %d %f", &emp.emp_id, emp.name, &emp.age, &emp.salary) != EOF) {
        if (emp.emp_id == emp_id) {
            printf("\nEmployee ID: %d\n", emp.emp_id);
            printf("Name: %s\n", emp.name);
            printf("Age: %d\n", emp.age);
            printf("Salary: %.2f\n", emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee not found.\n");
    }

    fclose(fp);
}

// Function to update employee details
void update_employee() {
    int emp_id;
    int found = 0;
    Employee emp;
    FILE *fp, *temp_fp;

    printf("\n--- UPDATE EMPLOYEE ---\n");
    printf("Enter Employee ID to update: ");
    scanf("%d", &emp_id);

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening employee data file.\n");
        return;
    }

    temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %d %f", &emp.emp_id, emp.name, &emp.age, &emp.salary) != EOF) {
        if (emp.emp_id == emp_id) {
            printf("Enter new name: ");
            getchar();  // Consume leftover newline
            fgets(emp.name, sizeof(emp.name), stdin);
            emp.name[strcspn(emp.name, "\n")] = '\0';

            printf("Enter new age: ");
            scanf("%d", &emp.age);

            printf("Enter new salary: ");
            scanf("%f", &emp.salary);

            found = 1;
        }
        fprintf(temp_fp, "%d %s %d %.2f\n", emp.emp_id, emp.name, emp.age, emp.salary);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Employee updated successfully.\n");
    } else {
        remove("temp.txt");
        printf("Employee not found.\n");
    }
}

// Function to delete employee details
void delete_employee() {
    int emp_id;
    int found = 0;
    Employee emp;
    FILE *fp, *temp_fp;

    printf("\n--- DELETE EMPLOYEE ---\n");
    printf("Enter Employee ID to delete: ");
    scanf("%d", &emp_id);

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening employee data file.\n");
        return;
    }

    temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %d %f", &emp.emp_id, emp.name, &emp.age, &emp.salary) != EOF) {
        if (emp.emp_id != emp_id) {
            fprintf(temp_fp, "%d %s %d %.2f\n", emp.emp_id, emp.name, emp.age, emp.salary);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Employee deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("Employee not found.\n");
    }
}
