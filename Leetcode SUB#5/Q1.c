#include <stdio.h>
#include <stdlib.h>
void print(int **ptr, int arr[]) {
  for (int i = 0; i < 10; i++) {
    printf("\nROW %d -->", i + 1);
    for (int j = 0; j < arr[i]; j++) {
      printf("%d", ptr[i][j]);
    }
  }
}
int main() {
  int column_count[10];
  int **ptr = malloc(10 * sizeof(int *));
  for (int i = 0; i < 10; i++) {
    int n = 0;
    printf("Enter number of columns for row %d: ", i + 1);
    scanf("%d", &n);
    column_count[i] = n;
    ptr[i] = malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
      ptr[i][j] = i + 1;
    }
  }
  print(ptr, column_count);
  for (int i=0;i<10;i++){
    free(ptr[i]);
  }
  free(ptr);
  return 0;
}
