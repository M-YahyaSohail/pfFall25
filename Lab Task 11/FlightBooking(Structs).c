#include <stdio.h>
#include <string.h>

struct Flight {
    char flightNumber[20];
    char departureCity[50];
    char destinationCity[50];
    char date[20];
    int seats;
};

void displayDetails(struct Flight f) {
    printf("\n--- Flight Details ---\n");
    printf("Flight Number: %s\n", f.flightNumber);
    printf("Route: %s to %s\n", f.departureCity, f.destinationCity);
    printf("Date: %s\n", f.date);
    printf("Available Seats: %d\n", f.seats);
}

void bookSeat(struct Flight *f) {
    if (f->seats > 0) {
        f->seats = f->seats - 1;
        printf("\n[Success] Seat booked! Ticket confirmed.\n");
        printf("Remaining seats: %d\n", f->seats);
    } else {
        printf("\n[Error] Flight is full! No seats available.\n");
    }
}

int main() {
    struct Flight myFlight;
    int choice;

    printf("--- Enter Flight Information ---\n");
    printf("Enter Flight Number: ");
    scanf("%s", myFlight.flightNumber);
    
    printf("Enter Departure City: ");
    scanf("%s", myFlight.departureCity);
    
    printf("Enter Destination City: ");
    scanf("%s", myFlight.destinationCity);
    
    printf("Enter Date (dd/mm/yyyy): ");
    scanf("%s", myFlight.date);
    
    printf("Enter Total Seats: ");
    scanf("%d", &myFlight.seats);

    do {
        printf("\n=== FLIGHT MENU ===\n");
        printf("1. Display Flight Details\n");
        printf("2. Book a Seat\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayDetails(myFlight);
                break;
            case 2:
                bookSeat(&myFlight);
                break;
            case 3:
                printf("Exiting system.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}