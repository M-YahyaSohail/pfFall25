#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee employees[], int n) {
    printf("\n%-10s %-20s %-20s %-10s\n", "ID", "Name", "Designation", "Salary");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-20s %-10.2f\n", 
               employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
    }
}

void findHighestSalary(struct Employee employees[], int n) {
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (employees[i].salary > employees[maxIndex].salary) {
            maxIndex = i;
        }
    }
    printf("\n--- Highest Salary Employee ---\n");
    printf("ID: %d\nName: %s\nSalary: %.2f\n", 
           employees[maxIndex].id, employees[maxIndex].name, employees[maxIndex].salary);
}

void searchEmployee(struct Employee employees[], int n) {
    int choice;
    printf("\n--- Search Employee ---\n");
    printf("1. Search by ID\n2. Search by Name\nEnter choice: ");
    scanf("%d", &choice);

    int found = 0;
    if (choice == 1) {
        int searchID;
        printf("Enter Employee ID: ");
        scanf("%d", &searchID);
        for (int i = 0; i < n; i++) {
            if (employees[i].id == searchID) {
                printf("Found: %s (Designation: %s)\n", employees[i].name, employees[i].designation);
                found = 1;
                break;
            }
        }
    } else if (choice == 2) {
        char searchName[50];
        printf("Enter Employee Name: ");
        scanf(" %[^\n]s", searchName);
        for (int i = 0; i < n; i++) {
            if (strcmp(employees[i].name, searchName) == 0) {
                printf("Found: ID %d (Designation: %s)\n", employees[i].id, employees[i].designation);
                found = 1;
                break;
            }
        }
    } else {
        printf("Invalid choice.\n");
        return;
    }

    if (found == 0) {
        printf("Employee not found.\n");
    }
}

int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee employees[100];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &employees[i].id);
        printf("Name: ");
        scanf(" %[^\n]s", employees[i].name);
        printf("Designation: ");
        scanf(" %[^\n]s", employees[i].designation);
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }

    displayEmployees(employees, n);
    findHighestSalary(employees, n);
    searchEmployee(employees, n);

    return 0;
}
