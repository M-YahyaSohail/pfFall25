#include <stdio.h>
#include <stdlib.h>

void display_array(int *arr, int size) {
    printf("Current Array: {");
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], (i == size - 1) ? "" : ", ");
    }
    printf("}\n");
}

int *insert_sorted(int *arr, int *size, int new_element) {
    int old_size = *size;
    int new_size = old_size + 1;
    
    int *new_arr = realloc(arr, new_size * sizeof(int));
    if (new_arr == NULL) return arr;

    int i = old_size;
    while (i > 0 && new_arr[i - 1] > new_element) {
        new_arr[i] = new_arr[i - 1];
        i--;
    }
    new_arr[i] = new_element;

    *size = new_size;
    return new_arr;
}

int main() {
    int *ptr = NULL;
    int size = 0;
    int n, num;

    printf("How many numbers to insert? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &num);
        
        ptr = insert_sorted(ptr, &size, num);
        if (ptr == NULL) {
            printf("Reallocation failed. Stopping.\n");
            break;
        }
        display_array(ptr, size);
    }

    if (ptr != NULL) {
        free(ptr);
        ptr = NULL;
    }
    
    return 0;
}