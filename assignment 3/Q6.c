#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "members.dat"

typedef struct {
    int id;
    char fullName[100];
    char batch[20];
    char type[10]; 
    char regDate[15];
    char dob[15];
    char interest[20];
} Student;

Student *students = NULL;
int studentCount = 0;

void loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("No existing database found. Starting fresh.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    studentCount = fileSize / sizeof(Student);
    if (studentCount > 0) {
        students = (Student *)malloc(studentCount * sizeof(Student));
        if (fread(students, sizeof(Student), studentCount, fp) != studentCount) {
            printf("Error reading file data.\n");
        }
    }
    fclose(fp);
    printf("Database loaded. %d records found.\n", studentCount);
}

void saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error saving database");
        return;
    }
    if (studentCount > 0) {
        fwrite(students, sizeof(Student), studentCount, fp);
    }
    fclose(fp);
    printf("Database saved successfully.\n");
}

int isDuplicate(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) return 1;
    }
    return 0;
}

void addStudent() {
    Student s;
    printf("\n--- Register Student ---\n");
    printf("Enter ID: ");
    scanf("%d", &s.id);
    
    if (isDuplicate(s.id)) {
        printf("Error: Student ID %d already exists.\n", s.id);
        return;
    }

    printf("Enter Full Name: ");
    scanf(" %[^\n]s", s.fullName);
    printf("Enter Batch (CS/SE/AI/Cyber): ");
    scanf(" %[^\n]s", s.batch);
    printf("Membership Type (IEEE/ACM): ");
    scanf("%s", s.type);
    printf("Registration Date (YYYY-MM-DD): ");
    scanf("%s", s.regDate);
    printf("Date of Birth (YYYY-MM-DD): ");
    scanf("%s", s.dob);
    printf("Interest (IEEE/ACM/Both): ");
    scanf("%s", s.interest);

    studentCount++;
    students = (Student *)realloc(students, studentCount * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    students[studentCount - 1] = s;

    saveDatabase(FILE_NAME);
}

void displayStudents() {
    printf("\n%-5s %-20s %-10s %-10s %-10s\n", "ID", "Name", "Batch", "Type", "Interest");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%-5d %-20s %-10s %-10s %-10s\n", 
               students[i].id, students[i].fullName, students[i].batch, 
               students[i].type, students[i].interest);
    }
}

void updateStudent() {
    int id, found = 0;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("Updating %s...\n", students[i].fullName);
            printf("Enter New Batch: ");
            scanf(" %[^\n]s", students[i].batch);
            printf("Enter New Membership Type (IEEE/ACM): ");
            scanf("%s", students[i].type);
            printf("Enter New Interest: ");
            scanf("%s", students[i].interest);
            break;
        }
    }

    if (found) {
        saveDatabase(FILE_NAME);
    } else {
        printf("Student ID not found.\n");
    }
}

void deleteStudent() {
    int id, found = 0;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            students = (Student *)realloc(students, studentCount * sizeof(Student));
            break;
        }
    }

    if (found) {
        saveDatabase(FILE_NAME);
        printf("Student record deleted.\n");
    } else {
        printf("Student ID not found.\n");
    }
}

void generateReport() {
    char batch[20];
    printf("Enter Batch to filter (CS/SE/AI...): ");
    scanf("%s", batch);

    printf("\n--- Report for Batch: %s ---\n", batch);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batch) == 0) {
            printf("ID: %d | Name: %s | Type: %s\n", 
                   students[i].id, students[i].fullName, students[i].type);
        }
    }
}

int main() {
    loadDatabase(FILE_NAME);

    int choice;
    do {
        printf("\n=== IEEE/ACM Manager ===\n");
        printf("1. Register Student\n2. View All\n3. Update Student\n4. Delete Student\n5. Batch Report\n6. Exit\nChoice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: generateReport(); break;
            case 6: printf("Saving and Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);

    if (students) free(students);
    return 0;
}
