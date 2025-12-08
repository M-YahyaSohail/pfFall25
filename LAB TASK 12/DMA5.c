#include <stdio.h>
#include <stdlib.h>

void display(int *arr, int size) {
    printf("{");
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], (i == size - 1) ? "" : ", ");
    }
    printf("}\n");
}

int *remove_duplicates(int *arr, int *size) {
    int new_size = *size;
    int *temp_arr = malloc(new_size * sizeof(int));
    if (temp_arr == NULL) return NULL;

    int k = 0;
    int found_duplicates = 0;
    
    printf("\nDuplicates found: {");
    for (int i = 0; i < *size; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < k; j++) {
            if (arr[i] == temp_arr[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            temp_arr[k] = arr[i];
            k++;
        } else {
            printf("%d%s", arr[i], (found_duplicates++ > 0) ? ", " : "");
        }
    }
    printf("}\n");

    new_size = k;
    free(arr);
    arr = NULL;
    
    int *final_arr = realloc(temp_arr, new_size * sizeof(int));
    if (final_arr == NULL) {
        free(temp_arr);
        return NULL;
    }
    
    *size = new_size;
    return final_arr;
}

int main() {
    int n;
    printf("Enter array size: ");
    scanf("%d", &n);

    int *ptr = malloc(n * sizeof(int));
    if (ptr == NULL) return 1;

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ptr[i]);
    }

    printf("\nOriginal array: ");
    display(ptr, n);

    ptr = remove_duplicates(ptr, &n);
    if (ptr == NULL) return 1;

    printf("Final array (size %d): ", n);
    display(ptr, n);

    free(ptr);
    ptr = NULL;

    return 0;
}