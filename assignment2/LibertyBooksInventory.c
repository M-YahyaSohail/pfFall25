#include <stdio.h>

#define MAX_BOOKS 100

void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *count);
void processSale(int isbns[], float prices[], int quantities[], int count);
void showLowStock(int isbns[], char titles[][50], float prices[], int quantities[], int count);

int main()
{
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][50];
    float prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];
    int count = 0;
    int choice;

    do
    {
        printf("\n--- LIBERTY BOOKS STORE ---\n");
        printf("1. Add Book\n");
        printf("2. Sell Book\n");
        printf("3. Low Stock Report\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addBook(isbns, titles, prices, quantities, &count);
                break;
            case 2:
                processSale(isbns, prices, quantities, count);
                break;
            case 3:
                showLowStock(isbns, titles, prices, quantities, count);
                break;
            case 4:
                printf("\nExiting... Thank you!\n");
                break;
            default:
                printf("\nInvalid choice, try again.\n");
        }
    } while(choice != 4);

    return 0;
}

void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *count)
{
    int isbn, i, exists = 0;

    if(*count >= MAX_BOOKS)
    {
        printf("\nInventory full. Cannot add more books.\n");
        return;
    }

    printf("\nEnter ISBN: ");
    scanf("%d", &isbn);

    for(i = 0; i < *count; i++)
    {
        if(isbns[i] == isbn)
        {
            exists = 1;
            break;
        }
    }

    if(exists)
    {
        printf("\nBook with this ISBN already exists.\n");
    }
    else
    {
        isbns[*count] = isbn;
        printf("Enter Title: ");
        scanf(" %[^\n]", titles[*count]);
        printf("Enter Price: ");
        scanf("%f", &prices[*count]);
        printf("Enter Quantity: ");
        scanf("%d", &quantities[*count]);

        (*count)++;
        printf("\nBook added successfully!\n");
    }
}

void processSale(int isbns[], float prices[], int quantities[], int count)
{
    int isbn, qty, i, found = -1;

    if(count == 0)
    {
        printf("\nNo books in inventory.\n");
        return;
    }

    printf("\nEnter ISBN to sell: ");
    scanf("%d", &isbn);

    for(i = 0; i < count; i++)
    {
        if(isbns[i] == isbn)
        {
            found = i;
            break;
        }
    }

    if(found == -1)
    {
        printf("\nBook not found.\n");
    }
    else
    {
        printf("Enter quantity sold: ");
        scanf("%d", &qty);

        if(qty <= 0)
        {
            printf("\nInvalid quantity.\n");
        }
        else if(qty > quantities[found])
        {
            printf("\nNot enough stock. Available: %d\n", quantities[found]);
        }
        else
        {
            quantities[found] -= qty;
            printf("\nSale successful! Total: %.2f\n", qty * prices[found]);
            printf("Remaining stock: %d\n", quantities[found]);
        }
    }
}

void showLowStock(int isbns[], char titles[][50], float prices[], int quantities[], int count)
{
    int i, found = 0;

    if(count == 0)
    {
        printf("\nNo books in inventory.\n");
        return;
    }

    printf("\n--- LOW STOCK REPORT (less than 5) ---\n");

    for(i = 0; i < count; i++)
    {
        if(quantities[i] < 5)
        {
            printf("\nISBN: %d\n", isbns[i]);
            printf("Title: %s\n", titles[i]);
            printf("Price: %.2f\n", prices[i]);
            printf("Quantity: %d\n", quantities[i]);
            found = 1;
        }
    }

    if(!found)
    {
        printf("\nAll books have enough stock.\n");
    }
}


