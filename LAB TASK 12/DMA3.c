#include <stdio.h>
#include <stdlib.h>

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void display(char **ptr, int m) {
    printf("\nThe students id's are as follows:");
    for (int i = 0; i < m; i++) {
        printf("\nId for student %d: ", i + 1);
        for (int j = 0; j < 20; j++) {
            if (ptr[i][j] == '\n') {
                break;
            }
            printf("%c", ptr[i][j]);
        }
    }
}

int main() {
    int n = 3;
    char **ptr = malloc(n * sizeof(char *));
    if (ptr == NULL) return 1;

    for (int i = 0; i < n; i++) {
        ptr[i] = malloc(20 * sizeof(char));
        if (ptr[i] == NULL) {
            for (int k = 0; k < i; k++) free(ptr[k]);
            free(ptr);
            return 1;
        }
    }
    
    printf("\n---------Enter id's for students----------");
    for (int i = 0; i < n; i++) {
        printf("\nId for student %d: ", i + 1);
        for (int j = 0; j < 20; j++) {
            scanf("%c", &ptr[i][j]);
            if (ptr[i][j] == '\n') {
                break;
            }
        }
    }
    
    int m = 0;
    int d = n;
    int total = n;
    int ch;
    
    printf("Do you want to add new students? ('1' for YES and '0' for NO) ");
    scanf("%d", &ch);
    clear_input_buffer();
    
    if (ch == 1) {
        do {
            printf("Enter amount of new students: ");
            scanf("%d", &m);
            clear_input_buffer();
            
            int new_total = m + total;
            char **temp_ptr = realloc(ptr, new_total * sizeof(char *));
            if (temp_ptr == NULL) {
                printf("Reallocation failed. Stopping input.\n");
                break;
            }
            ptr = temp_ptr;
            total = new_total;

            for (int i = d; i < total; i++) {
                ptr[i] = malloc(20 * sizeof(char));
                if (ptr[i] == NULL) {
                    for (int k = 0; k < total; k++) free(ptr[k]);
                    free(ptr);
                    return 1;
                }
            }
            
            printf("\n---------Enter id's for students----------");
            for (int i = d; i < total; i++) {
                printf("\nId for student %d: ", i + 1);
                for (int j = 0; j < 20; j++) {
                    scanf("%c", &ptr[i][j]);
                    if (ptr[i][j] == '\n') {
                        break;
                    }
                }
            }
            
            printf(
                "\nDo you want to add new students? ('1' for YES and '0' for NO) ");
            scanf("%d", &ch);
            clear_input_buffer();
            d = total;
            
        } while (ch == 1);
    }
    
    display(ptr, total);
    
    for (int i = 0; i < total; i++) {
        free(ptr[i]);
        ptr[i] = NULL;
    }
    free(ptr);
    ptr = NULL;
    
    return 0;
}