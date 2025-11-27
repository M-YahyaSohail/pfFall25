#include <stdio.h>

struct Move {
    int disk;
    char fromRod;
    char toRod;
};

struct Move history[2000];
static int moveCount = 0;

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 0) {
        return;
    }

    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);

    printf("Move %d: Disk %d from %c to %c\n", moveCount + 1, n, from_rod, to_rod);

    history[moveCount].disk = n;
    history[moveCount].fromRod = from_rod;
    history[moveCount].toRod = to_rod;
    moveCount++;

    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n, choice;

    printf("--- Tower of Hanoi Solver ---\n");
    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n > 10) {
        printf("Warning: Number too high for this demo array. Setting n=10.\n");
        n = 10;
    }

    printf("\nSolving...\n");
    towerOfHanoi(n, 'A', 'C', 'B');

    printf("\nTotal moves made: %d\n", moveCount);

    do {
        printf("\n--- Move Inspector ---\n");
        printf("Enter a move number to view details (1 to %d) or 0 to Exit: ", moveCount);
        scanf("%d", &choice);

        if (choice > 0 && choice <= moveCount) {
            int index = choice - 1;
            struct Move m = history[index];

            printf("\n[Replay Move %d]\n", choice);
            printf("Disk: %d\n", m.disk);
            printf("Source Rod: %c\n", m.fromRod);
            printf("Destination Rod: %c\n", m.toRod);
        } else if (choice != 0) {
            printf("Invalid move number.\n");
        }

    } while (choice != 0);

    return 0;
}