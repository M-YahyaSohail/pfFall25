#include <stdio.h>
#include <string.h>

struct Movie {
    char title[100];
    char genre[50];
    char director[50];
    int year;
    float rating;
};

struct Movie library[100]; 
int count = 0;             


void addMovie() {
    printf("\n--- Add New Movie ---\n");
    
    
    printf("Enter Title: ");
    scanf(" %[^\n]s", library[count].title);

    printf("Enter Genre (e.g., Action, Drama): ");
    scanf(" %[^\n]s", library[count].genre);

    printf("Enter Director: ");
    scanf(" %[^\n]s", library[count].director);

    printf("Enter Release Year: ");
    scanf("%d", &library[count].year);

    printf("Enter Rating (0.0 - 10.0): ");
    scanf("%f", &library[count].rating);

    count++; 
    printf("Movie added successfully!\n");
}

void displayAll() {
    printf("\n--- All Movies ---\n");
    if (count == 0) {
        printf("No movies in the library.\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("%d. %s | %s | Rating: %.1f\n", 
                   i+1, library[i].title, library[i].genre, library[i].rating);
        }
    }
}

void searchByGenre() {
    char searchGenre[50];
    int found = 0;

    printf("\n--- Search by Genre ---\n");
    printf("Enter genre to search: ");
    scanf(" %[^\n]s", searchGenre);

    printf("\nResults:\n");
    for (int i = 0; i < count; i++) {
        
        if (strcmp(library[i].genre, searchGenre) == 0) {
            printf("Found: %s (Dir: %s, Year: %d)\n", 
                   library[i].title, library[i].director, library[i].year);
            found = 1;
        }
    }

    if (found == 0) {
        printf("No movies found for this genre.\n");
    }
}


int main() {
    int choice;

    do {
        printf("\n=== MOVIE MANAGEMENT SYSTEM ===\n");
        printf("1. Add New Movie\n");
        printf("2. Search by Genre\n");
        printf("3. Display All Movies\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMovie();
                break;
            case 2:
                searchByGenre();
                break;
            case 3:
                displayAll();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}