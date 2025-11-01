#include <stdio.h>
#include <string.h>

void encodeMessage(char message[]);
void decodeMessage(char message[]);
void reverseString(char str[]);
char toggleBits(char c);
void clearInputBuffer();

int main()
{
    int menuChoice;
    char message[200];
    
    do
    {
        printf("\n--- TCS Message Utility ---\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);
        clearInputBuffer(); 

        switch(menuChoice)
        {
            case 1:
            {
                printf("\nEnter message to encode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0; 
                
                encodeMessage(message);
                printf("\nEncoded Message: %s\n", message);
                break;
            }
            case 2:
            {
                printf("\nEnter message to decode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                
                decodeMessage(message);
                printf("\nDecoded Message: %s\n", message);
                break;
            }
            case 3:
            {
                printf("\nExiting program.\n");
                break;
            }
            default:
            {
                printf("\nInvalid choice. Please try again.\n");
            }
        }
        
    } while(menuChoice != 3);
    
    return 0;
}

void clearInputBuffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void reverseString(char str[])
{
    int left = 0;
    int right = strlen(str) - 1;
    char temp;
    
    while(left < right)
    {
        temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        
        left++;
        right--;
    }
}

char toggleBits(char c)
{
    
    char mask = (1 << 1) | (1 << 4); 
    
    return c ^ mask;
}

void encodeMessage(char message[])
{
    int i;
    int len = strlen(message);
    
    reverseString(message);
    
    for(i = 0; i < len; i++)
    {
        message[i] = toggleBits(message[i]);
    }
}

void decodeMessage(char message[])
{
    int i;
    int len = strlen(message);
    
    for(i = 0; i < len; i++)
    {
        message[i] = toggleBits(message[i]);
    }
    
    reverseString(message);
}