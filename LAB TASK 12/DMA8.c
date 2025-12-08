#include <stdio.h>
#include <stdlib.h>

int main() {
    int *allocations[5];
    int total_allocated = 0;
    int total_freed = 0;
    
    printf("--- Memory Allocation Cycle ---\n");
    for (int i = 0; i < 5; i++) {
        allocations[i] = (int *)malloc(sizeof(int));
        if (allocations[i] == NULL) break;
        *allocations[i] = (i + 1) * 10;
        total_allocated += sizeof(int);
    }

    printf("Total memory allocated: %d bytes\n", total_allocated);

    printf("--- Intentionally Losing Pointers ---\n");
    printf("Losing allocation[1] (Value: %d)\n", *allocations[1]);
    int *lost_ptr_1 = allocations[1];
    allocations[1] = NULL; 

    printf("Losing allocation[3] (Value: %d)\n", *allocations[3]);
    int *lost_ptr_2 = allocations[3];
    allocations[3] = NULL; 

    printf("--- Proper Freeing of Accessible Pointers ---\n");
    for (int i = 0; i < 5; i += 2) {
        if (allocations[i] != NULL) {
            printf("Freeing allocation[%d] (Value: %d)\n", i, *allocations[i]);
            free(allocations[i]);
            allocations[i] = NULL;
            total_freed += sizeof(int);
        }
    }
    
    printf("\n--- Memory Leak Report ---\n");
    printf("Total allocated: %d bytes\n", total_allocated);
    printf("Total freed: %d bytes\n", total_freed);
    printf("Leaked memory (bytes): %d\n", total_allocated - total_freed);
    printf("Leaked allocations count: %d\n", 5 - (total_freed / (int)sizeof(int)));
    printf("Leaked addresses (from lost pointers): %p and %p\n", (void *)lost_ptr_1, (void *)lost_ptr_2);

    return 0;
}