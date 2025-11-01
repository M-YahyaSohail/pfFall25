#include <stdio.h>

#define GRID_SIZE 5 
#define POWER_ON 1  
#define OVERLOAD 2  
#define MAINTENANCE 4 

void updateSectorStatus(int grid[][GRID_SIZE]);
void querySectorStatus(int grid[][GRID_SIZE]);
void runSystemDiagnostic(int grid[][GRID_SIZE]);
void initializeGrid(int grid[][GRID_SIZE]);

int main()
{
    int grid[GRID_SIZE][GRID_SIZE];
    int menuChoice;
    
    initializeGrid(grid); 

    do
    {
        printf("\n--- IESCO Power Grid Monitor (ICT) ---\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);

        switch(menuChoice)
        {
            case 1:
                updateSectorStatus(grid);
                break;
            case 2:
                querySectorStatus(grid);
                break;
            case 3:
                runSystemDiagnostic(grid);
                break;
            case 4:
                printf("\nExiting system.\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while(menuChoice != 4);

    return 0;
}

void initializeGrid(int grid[][GRID_SIZE])
{
    int i, j;
    for(i = 0; i < GRID_SIZE; i++)
    {
        for(j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void updateSectorStatus(int grid[][GRID_SIZE])
{
    int row, col;
    int flagChoice;
    int statusChoice;
    int mask;

    printf("\nEnter sector coordinates (row col): ");
    scanf("%d %d", &row, &col);

    if(row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE)
    {
        printf("\nError: Invalid coordinates.\n");
        return;
    }

    printf("Select flag to update:\n");
    printf("  1. Power Status\n");
    printf("  2. Overload Warning\n");
    printf("  3. Maintenance Required\n");
    printf("Choice: ");
    scanf("%d", &flagChoice);

    switch(flagChoice)
    {
        case 1:
            mask = POWER_ON;
            break;
        case 2:
            mask = OVERLOAD;
            break;
        case 3:
            mask = MAINTENANCE;
            break;
        default:
            printf("\nError: Invalid flag choice.\n");
            return;
    }

    printf("Select status:\n");
    printf("  1. Set (ON / Yes)\n");
    printf("  0. Clear (OFF / No)\n");
    printf("Choice: ");
    scanf("%d", &statusChoice);

    if(statusChoice == 1)
    {
        grid[row][col] = grid[row][col] | mask;
        printf("\nSuccess: Sector (%d, %d) flag SET.\n", row, col);
    }
    else if(statusChoice == 0)
    {
        grid[row][col] = grid[row][col] & (~mask);
        printf("\nSuccess: Sector (%d, %d) flag CLEARED.\n", row, col);
    }
    else
    {
        printf("\nError: Invalid status choice.\n");
    }
}

void querySectorStatus(int grid[][GRID_SIZE])
{
    int row, col;
    int status;

    printf("\nEnter sector coordinates to query (row col): ");
    scanf("%d %d", &row, &col);

    if(row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE)
    {
        printf("\nError: Invalid coordinates.\n");
        return;
    }

    status = grid[row][col];
    
    printf("\n--- Status Report for Sector (%d, %d) ---\n", row, col);

    if(status & POWER_ON)
    {
        printf("  Power Status: ON\n");
    }
    else
    {
        printf("  Power Status: OFF\n");
    }

    if(status & OVERLOAD)
    {
        printf("  Overload Warning: YES (Overloaded)\n");
    }
    else
    {
        printf("  Overload Warning: NO (Normal)\n");
    }
    
    if(status & MAINTENANCE)
    {
        printf("  Maintenance: YES (Required)\n");
    }
    else
    {
        printf("  Maintenance: NO (Not Required)\n");
    }
}

void runSystemDiagnostic(int grid[][GRID_SIZE])
{
    int overloadCount = 0;
    int maintenanceCount = 0;
    int i, j;

    for(i = 0; i < GRID_SIZE; i++)
    {
        for(j = 0; j < GRID_SIZE; j++)
        {
            int status = grid[i][j];

            if(status & OVERLOAD)
            {
                overloadCount++;
            }
            if(status & MAINTENANCE)
            {
                maintenanceCount++;
            }
        }
    }

    printf("\n--- System Diagnostic Report ---\n");
    printf("Total Sectors Scanned: %d\n", GRID_SIZE * GRID_SIZE);
    printf("Sectors Overloaded:    %d\n", overloadCount);
    printf("Sectors Req. Maint.:   %d\n", maintenanceCount);
    printf("--------------------------------\n");
}
