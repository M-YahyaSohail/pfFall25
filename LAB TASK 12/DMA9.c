#include <stdio.h>
#include <stdlib.h>

int **allocate_matrix(int R, int C) {
    int **mat = (int **)malloc(R * sizeof(int *)); 
    if (mat == NULL) return NULL;

    for (int i = 0; i < R; i++) {
        mat[i] = (int *)malloc(C * sizeof(int));
        if (mat[i] == NULL) {
            for (int k = 0; k < i; k++) free(mat[k]);
            free(mat);
            return NULL;
        }
    }
    return mat;
}

void free_matrix(int **mat, int R) {
    if (mat == NULL) return;
    for (int i = 0; i < R; i++) {
        if (mat[i] != NULL) free(mat[i]);
    }
    free(mat);
}

void display_matrix(int **mat, int R, int C, const char *name) {
    printf("\n--- %s (%dx%d) ---\n", name, R, C);
    for (int i = 0; i < R; i++) {
        printf("|");
        for (int j = 0; j < C; j++) {
            printf(" %4d ", mat[i][j]);
        }
        printf("|\n");
    }
}

int **transpose_matrix(int **mat, int R, int C) {
    int **transposed = allocate_matrix(C, R);
    if (transposed == NULL) return NULL;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            transposed[j][i] = mat[i][j];
        }
    }
    return transposed;
}

int main() {
    int R, C;
    printf("Enter number of rows (R): ");
    scanf("%d", &R);
    printf("Enter number of columns (C): ");
    scanf("%d", &C);

    int **matrix = allocate_matrix(R, C);
    if (matrix == NULL) return 1;

    printf("\nEnter matrix elements:\n");
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("Enter [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    int **transposed = transpose_matrix(matrix, R, C);
    if (transposed == NULL) {
        free_matrix(matrix, R);
        return 1;
    }

    display_matrix(matrix, R, C, "Original Matrix");
    display_matrix(transposed, C, R, "Transposed Matrix");

    free_matrix(matrix, R);
    free_matrix(transposed, C);

    return 0;
}