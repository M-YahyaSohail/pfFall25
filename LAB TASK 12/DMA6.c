#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char temp_buffer[100];
    
    printf("Enter string 1: ");
    fgets(temp_buffer, 100, stdin);
    temp_buffer[strcspn(temp_buffer, "\n")] = 0;

    int len1 = strlen(temp_buffer);
    char *str1 = malloc((len1 + 1) * sizeof(char));
    if (str1 == NULL) return 1;
    strcpy(str1, temp_buffer);

    printf("Enter string 2: ");
    fgets(temp_buffer, 100, stdin);
    temp_buffer[strcspn(temp_buffer, "\n")] = 0;

    int len2 = strlen(temp_buffer);
    char *str2 = malloc((len2 + 1) * sizeof(char));
    if (str2 == NULL) {
        free(str1);
        return 1;
    }
    strcpy(str2, temp_buffer);

    int len3 = len1 + len2;
    char *str3 = malloc((len3 + 1) * sizeof(char));
    if (str3 == NULL) {
        free(str1);
        free(str2);
        return 1;
    }

    int k = 0;
    for (int i = 0; i < len1; i++) {
        str3[k++] = str1[i];
    }
    for (int i = 0; i < len2; i++) {
        str3[k++] = str2[i];
    }
    str3[len3] = '\0';

    printf("\nResult of Concatenation: %s\n", str3);

    free(str1);
    str1 = NULL;
    free(str2);
    str2 = NULL;
    free(str3);
    str3 = NULL;

    return 0;
}