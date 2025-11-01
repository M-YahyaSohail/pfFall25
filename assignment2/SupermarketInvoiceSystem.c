#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100
#define INVENTORY_SIZE 4

void getCustomer(char name[], char cnic[], int *hasCustomer);
void showInventory(int codes[], int stock[], float prices[]);
void addToCart(int codes[], int stock[], int cartCodes[], int cartQty[], int *cartCount);
void checkout(char name[], char cnic[], int hasCustomer, int cartCodes[], int cartQty[], int *cartCount, int invCodes[], int invStock[], float invPrices[]);
float getTotal(int cartCodes[], int cartQty[], int cartCount, int invCodes[], float invPrices[]);
void updateInventory(int cartCodes[], int cartQty[], int cartCount, int invCodes[], int invStock[]);

int main()
{
    int invCodes[INVENTORY_SIZE] = {1, 2, 3, 4};
    int invStock[INVENTORY_SIZE] = {50, 10, 20, 8};
    float invPrices[INVENTORY_SIZE] = {100.0, 200.0, 300.0, 150.0};

    char customerName[50];
    char customerCnic[20];
    int hasCustomer = 0;

    int cartCodes[MAX_ITEMS];
    int cartQty[MAX_ITEMS];
    int cartCount = 0;

    int choice;

    do
    {
        printf("\n--- SUPERMARKET MENU ---\n");
        printf("1. Enter Customer Info\n");
        printf("2. Show Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Checkout\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                getCustomer(customerName, customerCnic, &hasCustomer);
                break;
            case 2:
                showInventory(invCodes, invStock, invPrices);
                break;
            case 3:
                addToCart(invCodes, invStock, cartCodes, cartQty, &cartCount);
                break;
            case 4:
                checkout(customerName, customerCnic, hasCustomer, cartCodes, cartQty, &cartCount, invCodes, invStock, invPrices);
                break;
            case 5:
                printf("\nExiting system...\n");
                break;
            default:
                printf("\nInvalid choice, try again.\n");
        }

    } while(choice != 5);

    return 0;
}

void getCustomer(char name[], char cnic[], int *hasCustomer)
{
    printf("\nEnter Name: ");
    scanf(" %[^\n]", name);
    printf("Enter CNIC: ");
    scanf(" %[^\n]", cnic);

    *hasCustomer = 1;
    printf("\nCustomer saved.\n");
}

void showInventory(int codes[], int stock[], float prices[])
{
    int i;
    printf("\n--- AVAILABLE ITEMS ---\n");
    printf("Code\tStock\tPrice\n");
    printf("--------------------------\n");

    for(i = 0; i < INVENTORY_SIZE; i++)
    {
        printf("%d\t%d\t%.2f\n", codes[i], stock[i], prices[i]);
    }
}

void addToCart(int codes[], int stock[], int cartCodes[], int cartQty[], int *cartCount)
{
    int code, qty, i, found = -1;

    if(*cartCount >= MAX_ITEMS)
    {
        printf("\nCart full!\n");
        return;
    }

    printf("\nEnter Product Code: ");
    scanf("%d", &code);

    for(i = 0; i < INVENTORY_SIZE; i++)
    {
        if(codes[i] == code)
        {
            found = i;
            break;
        }
    }

    if(found == -1)
    {
        printf("\nInvalid product code.\n");
    }
    else
    {
        printf("Enter Quantity: ");
        scanf("%d", &qty);

        if(qty <= 0)
            printf("\nInvalid quantity.\n");
        else if(qty > stock[found])
            printf("\nNot enough stock. Only %d available.\n", stock[found]);
        else
        {
            cartCodes[*cartCount] = code;
            cartQty[*cartCount] = qty;
            (*cartCount)++;
            printf("\nItem added to cart.\n");
        }
    }
}

void checkout(char name[], char cnic[], int hasCustomer, int cartCodes[], int cartQty[], int *cartCount, int invCodes[], int invStock[], float invPrices[])
{
    if(!hasCustomer)
    {
        printf("\nEnter customer info first.\n");
        return;
    }

    if(*cartCount == 0)
    {
        printf("\nCart is empty.\n");
        return;
    }

    float total = getTotal(cartCodes, cartQty, *cartCount, invCodes, invPrices);
    float discount = 0, final = total;
    char code[20];

    printf("\nEnter promo code (Eid2025 or No): ");
    scanf("%s", code);

    if(strcmp(code, "Eid2025") == 0)
    {
        discount = total * 0.25;
        final = total - discount;
        printf("\nPromo applied! 25%% off.\n");
    }

    printf("\n--- INVOICE ---\n");
    printf("Customer: %s\n", name);
    printf("CNIC: %s\n", cnic);
    printf("-------------------\n");
    printf("Total: %.2f\n", total);
    printf("Discount: %.2f\n", discount);
    printf("Final: %.2f\n", final);
    printf("-------------------\n");
    printf("Thank you for shopping!\n");

    updateInventory(cartCodes, cartQty, *cartCount, invCodes, invStock);
    *cartCount = 0;
}

float getTotal(int cartCodes[], int cartQty[], int cartCount, int invCodes[], float invPrices[])
{
    float total = 0;
    int i, j;

    for(i = 0; i < cartCount; i++)
    {
        for(j = 0; j < INVENTORY_SIZE; j++)
        {
            if(cartCodes[i] == invCodes[j])
            {
                total += cartQty[i] * invPrices[j];
                break;
            }
        }
    }

    return total;
}

void updateInventory(int cartCodes[], int cartQty[], int cartCount, int invCodes[], int invStock[])
{
    int i, j;

    for(i = 0; i < cartCount; i++)
    {
        for(j = 0; j < INVENTORY_SIZE; j++)
        {
            if(cartCodes[i] == invCodes[j])
            {
                invStock[j] -= cartQty[i];
                break;
            }
        }
    }

    printf("\nStock updated.\n");
}
