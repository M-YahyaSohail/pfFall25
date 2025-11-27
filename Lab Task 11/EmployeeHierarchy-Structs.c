#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    double salary;
    struct Employee *manager; 
};

struct Department {
    char name[50];
    struct Employee employees[100];
    int empCount;
    struct Employee *head;
};

struct Department dept;

int generateID() {
    static int idCounter = 1000;
    return ++idCounter;
}

double calculateTotalSalaryExpense(struct Employee *emp) {
    double total = emp->salary;
    for (int i = 0; i < dept.empCount; i++) {
        if (dept.employees[i].manager == emp) {
            total += calculateTotalSalaryExpense(&dept.employees[i]);
        }
    }
    return total;
}

void printReportingChain(struct Employee *emp) {
    printf("%s", emp->name);
    if (emp->manager != NULL) {
        printf(" -> ");
        printReportingChain(emp->manager);
    } else {
        printf(" -> [CEO/Top]\n");
    }
}

int countLevels(struct Employee *emp) {
    int maxDepth = 0;
    for (int i = 0; i < dept.empCount; i++) {
        if (dept.employees[i].manager == emp) {
            int depth = countLevels(&dept.employees[i]);
            if (depth > maxDepth) maxDepth = depth;
        }
    }
    return 1 + maxDepth;
}

void displaySubordinates(struct Employee *emp) {
    for (int i = 0; i < dept.empCount; i++) {
        if (dept.employees[i].manager == emp) {
            printf("  - %s (%s)\n", dept.employees[i].name, dept.employees[i].designation);
            displaySubordinates(&dept.employees[i]);
        }
    }
}

void addEmployee() {
    int id = generateID();
    struct Employee *newEmp = &dept.employees[dept.empCount];
    newEmp->id = id;
    
    printf("Generated ID: %d\n", id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", newEmp->name);
    printf("Enter Designation: ");
    scanf(" %[^\n]s", newEmp->designation);
    printf("Enter Salary: ");
    scanf("%lf", &newEmp->salary);

    if (dept.empCount == 0) {
        newEmp->manager = NULL;
        printf("Set as Department Head/CEO.\n");
    } else {
        int mgrID;
        printf("Enter Manager ID: ");
        scanf("%d", &mgrID);
        newEmp->manager = NULL;
        for (int i = 0; i < dept.empCount; i++) {
            if (dept.employees[i].id == mgrID) {
                newEmp->manager = &dept.employees[i];
                break;
            }
        }
        if (newEmp->manager == NULL) {
            printf("Manager ID not found. Set to Top Level.\n");
        }
    }
    dept.empCount++;
}

int main() {
    dept.empCount = 0;
    int choice, searchID;

    do {
        printf("\n1. Add Employee\n2. Total Salary Expense (Recursive)\n3. Reporting Chain\n4. Org Levels\n5. Display Subordinates\n6. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) addEmployee();
        else if (choice >= 2 && choice <= 5) {
            printf("Enter Employee ID: ");
            scanf("%d", &searchID);
            struct Employee *target = NULL;
            for(int i=0; i<dept.empCount; i++) {
                if(dept.employees[i].id == searchID) target = &dept.employees[i];
            }

            if(target) {
                if (choice == 2) printf("Total Expense: %.2f\n", calculateTotalSalaryExpense(target));
                if (choice == 3) printReportingChain(target);
                if (choice == 4) printf("Levels below this employee: %d\n", countLevels(target));
                if (choice == 5) displaySubordinates(target);
            } else {
                printf("Employee not found.\n");
            }
        }
    } while (choice != 6);

    return 0;
}