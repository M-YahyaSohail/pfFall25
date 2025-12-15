#include <stdio.h>
#include <stdlib.h>

int **create_matrix(int m, int n) {
    
   
    int **p = (int**)malloc(m * sizeof(int*));
    if (p == NULL){
        return NULL;
    } 
    
    int *data = (int*)malloc(m * n * sizeof(int));
    if (data == NULL) {
        free(p);
        return NULL;
    }
    
    for (int i = 0; i < m; i++) {
        p[i] = data + (i * n); 
    }
    
    return p;
}

void destroy_matrix_optimized(int **p) {
    if (p == NULL){
        return; 
    } 
    
    free(p[0]); 

    free(p);
    
}
