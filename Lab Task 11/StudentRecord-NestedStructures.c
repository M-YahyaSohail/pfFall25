#include <stdio.h>
#include <string.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Address {
    char houseNumber[20];
    char street[50];
    char city[50];
    int postalCode;
};

struct Course {
    char courseCode[20];
    char courseName[50];
    int creditHours;
    float grade; 
};

struct Student {
    int studentID;
    char name[50];
    struct Date dob;
    struct Address address;
    struct Course courses[5];
    float cgpa;
};

struct Student students[100];
int count = 0;

void calculateCGPA(int index) {
    float totalPoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < 5; i++) {
        totalPoints += students[index].courses[i].grade * students[index].courses[i].creditHours;
        totalCredits += students[index].courses[i].creditHours;
    }

    if (totalCredits > 0) {
        students[index].cgpa = totalPoints / totalCredits;
    } else {
        students[index].cgpa = 0.0;
    }
}

void addStudent() {
    printf("\n--- Add New Student ---\n");
    
    printf("Enter Student ID: ");
    scanf("%d", &students[count].studentID);
    
    printf("Enter Name: ");
    scanf(" %[^\n]s", students[count].name);

    printf("Enter Date of Birth (day month year): ");
    scanf("%d %d %d", &students[count].dob.day, &students[count].dob.month, &students[count].dob.year);

    printf("\n-- Address Details --\n");
    printf("Enter House Number: ");
    scanf(" %[^\n]s", students[count].address.houseNumber);
    printf("Enter Street: ");
    scanf(" %[^\n]s", students[count].address.street);
    printf("Enter City: ");
    scanf(" %[^\n]s", students[count].address.city);
    printf("Enter Postal Code: ");
    scanf("%d", &students[count].address.postalCode);

    printf("\n-- Course Details (Enter 5 Courses) --\n");
    for (int i = 0; i < 5; i++) {
        printf("Course %d Code: ", i + 1);
        scanf(" %[^\n]s", students[count].courses[i].courseCode);
        
        printf("Course %d Name: ", i + 1);
        scanf(" %[^\n]s", students[count].courses[i].courseName);
        
        printf("Credit Hours: ");
        scanf("%d", &students[count].courses[i].creditHours);
        
        printf("Grade (0.0 - 4.0): ");
        scanf("%f", &students[count].courses[i].grade);
        printf("\n");
    }

    calculateCGPA(count);
    printf("Student added successfully! CGPA: %.2f\n", students[count].cgpa);
    count++;
}

void searchStudent() {
    int searchID;
    int found = 0;

    printf("\n--- Search Student by ID ---\n");
    printf("Enter Student ID: ");
    scanf("%d", &searchID);

    for (int i = 0; i < count; i++) {
        if (students[i].studentID == searchID) {
            found = 1;
            printf("\nID: %d | Name: %s | CGPA: %.2f\n", 
                   students[i].studentID, students[i].name, students[i].cgpa);
            break;
        }
    }

    if (found == 0) {
        printf("Student not found.\n");
    }
}

void displayAboveThreshold() {
    float threshold;
    int found = 0;

    printf("\n--- Filter by CGPA ---\n");
    printf("Enter CGPA Threshold: ");
    scanf("%f", &threshold);

    printf("\nStudents with CGPA > %.2f:\n", threshold);
    for (int i = 0; i < count; i++) {
        if (students[i].cgpa > threshold) {
            printf("%s (ID: %d) - CGPA: %.2f\n", students[i].name, students[i].studentID, students[i].cgpa);
            found = 1;
        }
    }

    if (found == 0) {
        printf("No students found above this threshold.\n");
    }
}

int compareDates(struct Date d1, struct Date d2) {
    if (d1.year != d2.year)
        return d1.year - d2.year;
    if (d1.month != d2.month)
        return d1.month - d2.month;
    return d1.day - d2.day;
}

void findOldestYoungest() {
    if (count == 0) {
        printf("No students to compare.\n");
        return;
    }

    int oldestIndex = 0;
    int youngestIndex = 0;

    for (int i = 1; i < count; i++) {
        if (compareDates(students[i].dob, students[oldestIndex].dob) < 0) {
            oldestIndex = i;
        }
        if (compareDates(students[i].dob, students[youngestIndex].dob) > 0) {
            youngestIndex = i;
        }
    }

    printf("\n--- Age Analysis ---\n");
    printf("Oldest Student: %s (Born: %d/%d/%d)\n", 
           students[oldestIndex].name, 
           students[oldestIndex].dob.day, students[oldestIndex].dob.month, students[oldestIndex].dob.year);
           
    printf("Youngest Student: %s (Born: %d/%d/%d)\n", 
           students[youngestIndex].name, 
           students[youngestIndex].dob.day, students[youngestIndex].dob.month, students[youngestIndex].dob.year);
}

int main() {
    int choice;

    do {
        printf("\n=== STUDENT MANAGEMENT SYSTEM ===\n");
        printf("1. Add New Student\n");
        printf("2. Search by ID\n");
        printf("3. Display Students by CGPA Threshold\n");
        printf("4. Find Oldest & Youngest Students\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                displayAboveThreshold();
                break;
            case 4:
                findOldestYoungest();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}