#include <stdio.h>

#define MAX_SIZE 100

void push(int stack[], int* top, int maxSize);
void pop(int stack[], int* top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main()
{
    int stack[MAX_SIZE];
    int top = -1; 
    int menuChoice;

    do
    {
        printf("\n--- Stack Operations Menu ---\n");
        printf("1. PUSH (Insert)\n");
        printf("2. POP (Remove)\n");
        printf("3. PEEK (View Top)\n");
        printf("4. DISPLAY (Show All)\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);

        switch(menuChoice)
        {
            case 1:
                push(stack, &top, MAX_SIZE);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("\nExiting program.\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while(menuChoice != 5);
    
    return 0;
}

void push(int stack[], int* top, int maxSize)
{
    int value;

    if(*top >= maxSize - 1)
    {
        printf("\nError: Stack Overflow. Cannot push.\n");
    }
    else
    {
        printf("\nEnter value to push: ");
        scanf("%d", &value);
        
        (*top)++; 
        stack[*top] = value; 
        
        printf("\nSuccess: %d was pushed onto the stack.\n", value);
    }
}

void pop(int stack[], int* top)
{
    int poppedValue;
    
    if(*top == -1)
    {
        printf("\nError: Stack Underflow. Cannot pop.\n");
    }
    else
    {
        poppedValue = stack[*top];
        (*top)--; 
        
        printf("\nSuccess: %d was popped from the stack.\n", poppedValue);
    }
}

void peek(int stack[], int top)
{
    if(top == -1)
    {
        printf("\nStack is empty. Nothing to peek.\n");
    }
    else
    {
        printf("\nThe top element is: %d\n", stack[top]);
    }
}

void display(int stack[], int top)
{
    int i;
    
    if(top == -1)
    {
        printf("\nStack is empty.\n");
    }
    else
    {
        printf("\nStack (Top to Bottom):\n");
        for(i = top; i >= 0; i--)
        {
            printf("%d\n", stack[i]);
        }
    }
}