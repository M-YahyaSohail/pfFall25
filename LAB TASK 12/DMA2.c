#include <stdio.h>
#include <stdlib.h>

void display_array(int *ptr, int n)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("%d", *(ptr + i));
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("}");
}

void reverse_array(int *ptr, int n)
{
    int temp;
    for (int i = 0; i < n / 2; i++)
    { 
        temp = ptr[i];
        ptr[i] = ptr[n - 1 - i];
        ptr[n - 1 - i] = temp;
    }
}

int main()
{
    int n;
    printf("Enter the amount of total numbers: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int *ptr = calloc(n, sizeof(int));
    if (ptr == NULL) return 1;

    for (int i = 0; i < n; i++)
    {
        printf("Enter %d number: ", i + 1);
        scanf("%d", ptr + i);
    }

    printf("\nThe original array is: ");
    display_array(ptr, n);

    reverse_array(ptr, n);
    
    printf("\nThe reversed array is: ");
    display_array(ptr, n);
    printf("\n");

    free(ptr);
    ptr = NULL;

    return 0;
}