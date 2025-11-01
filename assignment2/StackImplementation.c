#include <stdio.h>

#define MAX 100

void push(int stack[], int *top);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void show(int stack[], int top);

int main()
{
    int stack[MAX];
    int top = -1;
    int choice;

    do
    {
        printf("\n--- STACK MENU ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Show Stack\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                push(stack, &top);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                show(stack, top);
                break;
            case 5:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while(choice != 5);

    return 0;
}

void push(int stack[], int *top)
{
    int num;

    if(*top >= MAX - 1)
    {
        printf("\nStack Overflow! Cannot push.\n");
    }
    else
    {
        printf("\nEnter number to push: ");
        scanf("%d", &num);
        (*top)++;
        stack[*top] = num;
        printf("\n%d pushed into stack.\n", num);
    }
}

void pop(int stack[], int *top)
{
    if(*top == -1)
    {
        printf("\nStack Underflow! Nothing to pop.\n");
    }
    else
    {
        printf("\n%d popped from stack.\n", stack[*top]);
        (*top)--;
    }
}

void peek(int stack[], int top)
{
    if(top == -1)
    {
        printf("\nStack is empty.\n");
    }
    else
    {
        printf("\nTop element: %d\n", stack[top]);
    }
}

void show(int stack[], int top)
{
    int i;

    if(top == -1)
    {
        printf("\nStack is empty.\n");
    }
    else
    {
        printf("\nStack elements (top to bottom):\n");
        for(i = top; i >= 0; i--)
        {
            printf("%d\n", stack[i]);
        }
    }
}
