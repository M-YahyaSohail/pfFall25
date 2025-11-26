#include <stdio.h>
void rec(char *arr);
void rec (char *arr)
{
    if (*arr == '\0')
    {
        return;
    }
    else
    {
        rec(arr+1);
        printf("%c",*arr);
    }
}
int main()
{
    char arr[100];
    printf("Enter a string:");
   fgets(arr,sizeof(arr),stdin);
    rec(arr);
}