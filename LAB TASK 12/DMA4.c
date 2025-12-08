#include <stdio.h>
#include <stdlib.h>

int** sum(int **ptr, int **ptr1, int n, int m) {
    int **ptr2 = malloc(n * sizeof(int*));
    if (ptr2 == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        ptr2[i] = malloc(m * sizeof(int));
        if (ptr2[i] == NULL) {
            for (int k = 0; k < i; k++) free(ptr2[k]);
            free(ptr2);
            return NULL;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ptr2[i][j] = ptr[i][j] + ptr1[i][j];
        }
    }
    return ptr2;
}

void display_matrix(int **mat, int n, int m, const char *name) {
    printf("\n----------%s-----------\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == 0) {
                printf("|   ");
            }
            printf("%d   ", mat[i][j]);
            if (j == m - 1) {
                printf("|\n");
            }
        }
    }
}

void free_2d_matrix(int **mat, int n) {
    if (mat == NULL) return;
    for (int i = 0; i < n; i++) {
        free(mat[i]);
        mat[i] = NULL;
    }
    free(mat);
}

int main() {
    int n, m;
    printf("\nEnter number of rows: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;
    printf("\nEnter number of columns: ");
    if (scanf("%d", &m) != 1 || m <= 0) return 1;

    int **ptr = malloc(n * sizeof(int*));
    if (ptr == NULL) return 1;
    for (int i = 0; i < n; i++) {
        ptr[i] = malloc(m * sizeof(int));
        if (ptr[i] == NULL) {
            free_2d_matrix(ptr, i);
            return 1;
        }
    }
    
    int **ptr1 = malloc(n * sizeof(int*));
    if (ptr1 == NULL) { free_2d_matrix(ptr, n); return 1; }
    for (int i = 0; i < n; i++) {
        ptr1[i] = malloc(m * sizeof(int));
        if (ptr1[i] == NULL) { free_2d_matrix(ptr, n); free_2d_matrix(ptr1, i); return 1; }
    }

    printf("\nEnter data for matrix 1:");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("\nEnter number for [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &ptr[i][j]);
        }
    }
    printf("\nEnter data for matrix 2:");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("\nEnter number for [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &ptr1[i][j]);
        }
    }

    int **ptr2_sum = sum(ptr, ptr1, n, m);
    if (ptr2_sum == NULL) { free_2d_matrix(ptr, n); free_2d_matrix(ptr1, n); return 1; }

    display_matrix(ptr, n, m, "Matrix 1");
    display_matrix(ptr1, n, m, "Matrix 2");
    display_matrix(ptr2_sum, n, m, "Sum of the two matrix");

    free_2d_matrix(ptr, n);
    ptr = NULL;
    free_2d_matrix(ptr1, n);
    ptr1 = NULL;
    free_2d_matrix(ptr2_sum, n);
    ptr2_sum = NULL;

    return 0;
}