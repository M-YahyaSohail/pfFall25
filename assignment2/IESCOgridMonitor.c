#include <stdio.h>

#define SIZE 5

void initializeGrid(int power[][SIZE], int overload[][SIZE], int maintenance[][SIZE]);
void updateSector(int power[][SIZE], int overload[][SIZE], int maintenance[][SIZE]);
void viewSector(int power[][SIZE], int overload[][SIZE], int maintenance[][SIZE]);
void diagnostics(int power[][SIZE], int overload[][SIZE], int maintenance[][SIZE]);

int main() {
    int power[SIZE][SIZE];
    int overload[SIZE][SIZE];
    int maintenance[SIZE][SIZE];
    int choice;

    initializeGrid(power, overload, maintenance);

    do {
        printf("\n===== IESCO Power Grid Monitor =====\n");
        printf("1. Update Sector Status\n");
        printf("2. View Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateSector(power, overload, maintenance);
                break;
            case 2:
                viewSector(power, overload, maintenance);
                break;
            case 3:
                diagnostics(power, overload, maintenance);
                break;
            case 4:
                printf("\nExiting system... Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}

void initializeGrid(int power[][SIZE], int overload[][SIZE], int maintenance[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            power[i][j] = 0;
            overload[i][j] = 0;
            maintenance[i][j] = 0;
        }
    }
}

void updateSector(int power[][SIZE], int overload[][SIZE], int maintenance[][SIZE]) {
    int row, col, choice, status;

    printf("\nEnter sector coordinates (row col): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        printf("Invalid coordinates! Please try again.\n");
        return;
    }

    printf("\nSelect what to update:\n");
    printf("1. Power\n");
    printf("2. Overload\n");
    printf("3. Maintenance\n");
    printf("Choice: ");
    scanf("%d", &choice);

    printf("Enter status (1 = ON/Yes, 0 = OFF/No): ");
    scanf("%d", &status);

    switch (choice) {
        case 1:
            power[row][col] = status;
            printf("Power status updated.\n");
            break;
        case 2:
            overload[row][col] = status;
            printf("Overload status updated.\n");
            break;
        case 3:
            maintenance[row][col] = status;
            printf("Maintenance status updated.\n");
            break;
        default:
            printf("Invalid option!\n");
    }
}

void viewSector(int power[][SIZE], int overload[][SIZE], int maintenance[][SIZE]) {
    int row, col;

    printf("\nEnter sector coordinates (row col): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("\n--- Sector (%d, %d) Status ---\n", row, col);
    printf("Power: %s\n", power[row][col] ? "ON" : "OFF");
    printf("Overload: %s\n", overload[row][col] ? "YES" : "NO");
    printf("Maintenance: %s\n", maintenance[row][col] ? "REQUIRED" : "NOT REQUIRED");
}

void diagnostics(int power[][SIZE], int overload[][SIZE], int maintenance[][SIZE]) {
    int total = SIZE * SIZE;
    int overloadCount = 0;
    int maintenanceCount = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (overload[i][j])
                overloadCount++;
            if (maintenance[i][j])
                maintenanceCount++;
        }
    }

    printf("\n===== System Diagnostic Report =====\n");
    printf("Total sectors: %d\n", total);
    printf("Overloaded sectors: %d\n", overloadCount);
    printf("Maintenance required: %d\n", maintenanceCount);
    printf("====================================\n");
}
