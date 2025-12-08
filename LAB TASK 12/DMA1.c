#include <stdio.h>
#include <stdlib.h>

void sum_and_average(int num, int *ptr)
{
    float sum = 0;
    for (int i = 0; i < num; i++)
    {
        sum = sum + *(ptr + i);
    }
    printf("\nThe sum is: %.2f", sum);
    printf("\nThe average is: %.2f", sum / num);
}

int main()
{
    int n;
    printf("Enter the amount of total numbers: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int *ptr = malloc(n * sizeof(int));
    if (ptr == NULL) return 1;

    for (int i = 0; i < n; i++)
    {
        printf("Enter %d number: ", i + 1);
        scanf("%d", ptr + i);
    }

    sum_and_average(n, ptr);

    free(ptr);
    ptr = NULL;

    return 0;
}
