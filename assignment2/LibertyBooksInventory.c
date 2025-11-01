#include <stdio.h>

void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int* bookCount);
void processSale(int isbns[], float prices[], int quantities[], int bookCount);
void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount);

int main()
{
    int isbns[100];
    char titles[100][50];
    float prices[100];
    int quantities[100];
    int bookCount = 0; 
    int menuChoice;

    do
    {
        printf("\n--- Liberty Books Inventory System ---\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);

        switch(menuChoice)
        {
            case 1:
                addBook(isbns, titles, prices, quantities, &bookCount);
                break;
            case 2:
                processSale(isbns, prices, quantities, bookCount);
                break;
            case 3:
                generateLowStockReport(isbns, titles, prices, quantities, bookCount);
                break;
            case 4:
                printf("\nExiting system. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while(menuChoice != 4);

    return 0;
}

void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int* bookCount)
{
    int newIsbn;
    int i;
    int isDuplicate = 0;

    if(*bookCount >= 100)
    {
        printf("\nError: Inventory is full. Cannot add more books.\n");
        return;
    }

    printf("\nEnter new ISBN: ");
    scanf("%d", &newIsbn);

    for(i = 0; i < *bookCount; i++)
    {
        if(isbns[i] == newIsbn)
        {
            isDuplicate = 1;
            break;
        }
    }

    if(isDuplicate == 1)
    {
        printf("\nError: A book with this ISBN already exists.\n");
    }
    else
    {
        isbns[*bookCount] = newIsbn;
        
        printf("Enter book title: ");
        scanf(" %[^\n]", titles[*bookCount]); 
        
        printf("Enter book price: ");
        scanf("%f", &prices[*bookCount]);
        
        printf("Enter book quantity: ");
        scanf("%d", &quantities[*bookCount]);
        
        printf("\nSuccess: Book added to inventory.\n");
        
        (*bookCount)++;
    }
}

void processSale(int isbns[], float prices[], int quantities[], int bookCount)
{
    int searchIsbn;
    int saleQuantity;
    int foundIndex = -1;
    int i;

    if(bookCount == 0)
    {
        printf("\nError: Inventory is empty. Cannot process sale.\n");
        return;
    }

    printf("\nEnter ISBN of book sold: ");
    scanf("%d", &searchIsbn);

    for(i = 0; i < bookCount; i++)
    {
        if(isbns[i] == searchIsbn)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex == -1)
    {
        printf("\nError: Book with this ISBN not found.\n");
    }
    else
    {
        printf("Enter number of copies sold: ");
        scanf("%d", &saleQuantity);

        if(saleQuantity <= 0)
        {
            printf("\nError: Invalid quantity.\n");
        }
        else if(saleQuantity > quantities[foundIndex])
        {
            printf("\nError: Not enough stock. Only %d copies available.\n", quantities[foundIndex]);
        }
        else
        {
            quantities[foundIndex] = quantities[foundIndex] - saleQuantity;
            printf("\nSuccess: Sale processed. %.2f due.\n", saleQuantity * prices[foundIndex]);
            printf("Remaining stock for ISBN %d: %d\n", isbns[foundIndex], quantities[foundIndex]);
        }
    }
}

void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount)
{
    int i;
    int foundLowStock = 0;

    printf("\n--- Low-Stock Report (Quantity < 5) ---\n");
    printf("------------------------------------------\n");

    for(i = 0; i < bookCount; i++)
    {
        if(quantities[i] < 5)
        {
            printf("ISBN:     %d\n", isbns[i]);
            printf("Title:    %s\n", titles[i]);
            printf("Price:    %.2f\n", prices[i]);
            printf("Quantity: %d\n", quantities[i]);
            printf("------------------------------------------\n");
            foundLowStock = 1;
        }
    }

    if(foundLowStock == 0)
    {
        printf("No books are currently low in stock.\n");
    }
}

