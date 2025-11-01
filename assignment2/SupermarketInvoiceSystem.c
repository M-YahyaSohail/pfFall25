#include <stdio.h>
#include <string.h> 

void customerInfo(char customerName[], char customerCnic[], int* customerNameSet);
void displayInventory(int codes[], int stock[], float prices[]);
void addItemToCart(int invCodes[], int invStock[], int cartCodes[], int cartQuantities[], int* cartItemCount);
void showInvoice(char name[], char cnic[], int customerNameSet, int cartCodes[], int cartQuantities[], int* cartItemCount, int invCodes[], int invStock[], float invPrices[]);
void updateStock(int cartCodes[], int cartQuantities[], int cartItemCount, int invCodes[], int invStock[]);
float calculateBill(int cartCodes[], int cartQuantities[], int cartItemCount, int invCodes[], float invPrices[]);

int main()
{
    int inventoryCodes[4] = {1, 2, 3, 4};
    int inventoryStock[4] = {50, 10, 20, 8};
    float inventoryPrices[4] = {100.0, 200.0, 300.0, 150.0};
    
    char customerName[50];
    char customerCnic[20];
    int customerNameSet = 0; 

    int cartCodes[100];
    int cartQuantities[100];
    int cartItemCount = 0;

    int menuChoice;

    do
    {
        printf("\n--- Supermarket Billing System ---\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Show Invoice & Checkout\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);

        switch(menuChoice)
        {
            case 1:
                customerInfo(customerName, customerCnic, &customerNameSet);
                break;
            case 2:
                displayInventory(inventoryCodes, inventoryStock, inventoryPrices);
                break;
            case 3:
                addItemToCart(inventoryCodes, inventoryStock, cartCodes, cartQuantities, &cartItemCount);
                break;
            case 4:
                showInvoice(customerName, customerCnic, customerNameSet, cartCodes, cartQuantities, &cartItemCount, inventoryCodes, inventoryStock, inventoryPrices);
                break;
            case 5:
                printf("\nExiting system. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while(menuChoice != 5);

    return 0;
}

void customerInfo(char customerName[], char customerCnic[], int* customerNameSet)
{
    printf("\nEnter Customer Name: ");
    scanf(" %[^\n]", customerName);
    printf("Enter Customer CNIC: ");
    scanf(" %[^\n]", customerCnic);
    
    *customerNameSet = 1; 
    printf("\nCustomer information saved.\n");
}

void displayInventory(int codes[], int stock[], float prices[])
{
    int i;
    printf("\n--- Available Products ---\n");
    printf("Product Code\tQuantity in Stock\tPrice per Product\n");
    printf("----------------------------------------------------------\n");
    
    for(i = 0; i < 4; i++)
    {
        printf("%-15d\t%-17d\t%.2f\n", codes[i], stock[i], prices[i]);
    }
}

void addItemToCart(int invCodes[], int invStock[], int cartCodes[], int cartQuantities[], int* cartItemCount)
{
    int productCode;
    int quantity;
    int foundIndex = -1;
    int i;

    if(*cartItemCount >= 100)
    {
        printf("\nError: Cart is full.\n");
        return;
    }

    printf("\nEnter Product Code to add: ");
    scanf("%d", &productCode);
    
    for(i = 0; i < 4; i++)
    {
        if(invCodes[i] == productCode)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex == -1)
    {
        printf("\nError: Product code not found.\n");
    }
    else
    {
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        if(quantity <= 0)
        {
            printf("\nError: Invalid quantity.\n");
        }
        else if(quantity > invStock[foundIndex])
        {
            printf("\nError: Not enough stock. Only %d available.\n", invStock[foundIndex]);
        }
        else
        {
            cartCodes[*cartItemCount] = productCode;
            cartQuantities[*cartItemCount] = quantity;
            (*cartItemCount)++;
            printf("\nSuccess: Item added to cart.\n");
        }
    }
}

void showInvoice(char name[], char cnic[], int customerNameSet, int cartCodes[], int cartQuantities[], int* cartItemCount, int invCodes[], int invStock[], float invPrices[])
{
    float totalBill;
    float discountAmount = 0.0;
    float finalBill;
    char promoCode[20];
    int hasDiscount = 0;

    if(customerNameSet == 0)
    {
        printf("\nError: Please enter customer information (Option 1) first.\n");
        return;
    }

    if(*cartItemCount == 0)
    {
        printf("\nError: Your cart is empty. Please add items (Option 3) first.\n");
        return;
    }

    totalBill = calculateBill(cartCodes, cartQuantities, *cartItemCount, invCodes, invPrices);
    
    printf("\nDo you have a promocode? (Type 'Eid2025' or 'No'): ");
    scanf("%s", promoCode);

    if(strcmp(promoCode, "Eid2025") == 0)
    {
        hasDiscount = 1;
        discountAmount = totalBill * 0.25; 
        finalBill = totalBill - discountAmount;
        printf("Promocode 'Eid2025' applied!\n");
    }
    else
    {
        finalBill = totalBill;
    }

    printf("\n\n--- FINAL INVOICE ---\n");
    printf("Customer Name: %s\n", name);
    printf("Customer CNIC: %s\n", cnic);
    printf("--------------------------\n");
    printf("Total Bill (w/o discount): %.2f\n", totalBill);
    
    if(hasDiscount == 1)
    {
        printf("Discount (25%%):          -%.2f\n", discountAmount);
        printf("Final Bill (w/ discount):  %.2f\n", finalBill);
    }
    else
    {
        printf("Discount:                  N/A\n");
        printf("Final Bill:                %.2f\n", finalBill);
    }
    printf("--------------------------\n");
    printf("Thank you for shopping!\n\n");

    updateStock(cartCodes, cartQuantities, *cartItemCount, invCodes, invStock);
    
    *cartItemCount = 0;
    printf("Checkout complete. Inventory updated and cart cleared.\n");
}

float calculateBill(int cartCodes[], int cartQuantities[], int cartItemCount, int invCodes[], float invPrices[])
{
    float total = 0.0;
    int i, j;

    for(i = 0; i < cartItemCount; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(cartCodes[i] == invCodes[j])
            {
                total = total + (cartQuantities[i] * invPrices[j]);
                break; 
            }
        }
    }
    return total;
}

void updateStock(int cartCodes[], int cartQuantities[], int cartItemCount, int invCodes[], int invStock[])
{
    int i, j;
    
    for(i = 0; i < cartItemCount; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(cartCodes[i] == invCodes[j])
            {
                invStock[j] = invStock[j] - cartQuantities[i];
                break; 
            }
        }
    }
}
