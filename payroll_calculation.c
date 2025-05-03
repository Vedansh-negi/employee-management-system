#include <stdio.h>
#include <string.h>

// Define the payroll structure
struct payroll {
    int id;
    char name[30];
    float basesalary;
    int workingdays;
    int dayspresent;
    float overtimeHours;
    float deductions;
    float bonuses;
} employee;

// Function to add employee details
void addemp() {
    printf("Enter ID: ");
    scanf("%d", &employee.id);
    getchar();  // Flush newline from input buffer

    printf("Enter employee name: ");
    fgets(employee.name, sizeof(employee.name), stdin);
    employee.name[strcspn(employee.name, "\n")] = '\0'; // Remove newline

    printf("Enter base salary: ");
    scanf("%f", &employee.basesalary);

    printf("Enter working days: ");
    scanf("%d", &employee.workingdays);
}

// Function to mark attendance
void markAttendance() {
    printf("Enter number of days present: ");
    scanf("%d", &employee.dayspresent);
    if (employee.dayspresent > employee.workingdays) {
        printf("Days present can't be more than working days. Setting to max.\n");
        employee.dayspresent = employee.workingdays;
    }
}

#define OVERTIME_RATE 100  // Overtime pay per hour

// Function to calculate salary
float calculateSalary() {
    printf("Enter overtime hours: ");
    scanf("%f", &employee.overtimeHours);

    printf("Enter bonuses achieved by the employee: ");
    scanf("%f", &employee.bonuses);

    printf("Enter deductions for the employee: ");
    scanf("%f", &employee.deductions);

    float perDayPay = employee.basesalary / employee.workingdays;
    float baseSalEarned = perDayPay * employee.dayspresent;
    float overtimePay = employee.overtimeHours * OVERTIME_RATE;

    float grossSalary = baseSalEarned + overtimePay + employee.bonuses;
    float netSalary = grossSalary - employee.deductions;

    return netSalary;
}

// Function to display payslip
void displayPayslip(float netSalary) {
    printf("\n=========== PAYSLIP ===========\n");
    printf("Employee ID     : %d\n", employee.id);
    printf("Employee Name   : %s\n", employee.name);
    printf("Base Salary     : ₹%.2f\n", employee.basesalary);
    printf("Working Days    : %d\n", employee.workingdays);
    printf("Days Present    : %d\n", employee.dayspresent);
    printf("Overtime Hours  : %.2f\n", employee.overtimeHours);
    printf("Bonuses         : ₹%.2f\n", employee.bonuses);
    printf("Deductions      : ₹%.2f\n", employee.deductions);
    printf("Net Salary      : ₹%.2f\n", netSalary);
    printf("================================\n");
}

// Function to run payroll process
void generatePayroll() {
    addemp();
    markAttendance();
    float netSalary = calculateSalary();
    displayPayslip(netSalary);
}

// Interactive menu for payroll module
void payrollMenu() {
    int choice;
    float netSalary = 0.0;

    do {
        printf("\n==== Payroll Menu ====\n");
        printf("1. Add Employee Details\n");
        printf("2. Mark Attendance\n");
        printf("3. Calculate Salary\n");
        printf("4. Display Payslip\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addemp(); break;
            case 2: markAttendance(); break;
            case 3: netSalary = calculateSalary(); break;
            case 4: displayPayslip(netSalary); break;
            case 0: printf("Exiting payroll system...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}
