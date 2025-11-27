#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 2
#define BUFFER_SIZE 1024

char **lines = NULL;
int lineCount = 0;
int capacity = 0;

void checkMemory(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

void initEditor() {
    capacity = INITIAL_CAPACITY;
    lines = (char **)malloc(capacity * sizeof(char *));
    checkMemory(lines);
}

void insertLine(int index, const char *text) {
    if (index < 0 || index > lineCount) {
        printf("Error: Index out of bounds.\n");
        return;
    }

    if (lineCount == capacity) {
        capacity *= 2;
        lines = (char **)realloc(lines, capacity * sizeof(char *));
        checkMemory(lines);
    }

    if (index < lineCount) {
        memmove(&lines[index + 1], &lines[index], (lineCount - index) * sizeof(char *));
    }

    lines[index] = (char *)malloc((strlen(text) + 1) * sizeof(char));
    checkMemory(lines[index]);
    strcpy(lines[index], text);

    lineCount++;
    printf("Line inserted at %d.\n", index);
}

void deleteLine(int index) {
    if (index < 0 || index >= lineCount) {
        printf("Error: Invalid index.\n");
        return;
    }

    free(lines[index]);

    if (index < lineCount - 1) {
        memmove(&lines[index], &lines[index + 1], (lineCount - index - 1) * sizeof(char *));
    }

    lineCount--;
    printf("Line deleted at %d.\n", index);
}

void printAllLines() {
    printf("\n--- Editor Content ---\n");
    if (lineCount == 0) printf("(Empty)\n");
    for (int i = 0; i < lineCount; i++) {
        printf("%d: %s\n", i + 1, lines[i]);
    }
    printf("----------------------\n");
}

void shrinkToFit() {
    if (lineCount == 0) return;
    if (lineCount < capacity) {
        char **temp = (char **)realloc(lines, lineCount * sizeof(char *));
        if (temp != NULL) {
            lines = temp;
            capacity = lineCount;
            printf("Memory optimized. Capacity reduced to %d.\n", capacity);
        }
    }
}

void saveToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error saving file");
        return;
    }
    for (int i = 0; i < lineCount; i++) {
        fprintf(fp, "%s\n", lines[i]);
    }
    fclose(fp);
    printf("Saved to %s successfully.\n", filename);
}

void freeAll() {
    for (int i = 0; i < lineCount; i++) {
        free(lines[i]);
    }
    free(lines);
    lines = NULL;
    lineCount = 0;
    capacity = 0;
}

void loadFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    freeAll();
    initEditor();

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        buffer[strcspn(buffer, "\n")] = 0;
        insertLine(lineCount, buffer);
    }
    fclose(fp);
    printf("Loaded from %s.\n", filename);
}

int main() {
    initEditor();
    int choice, idx;
    char buffer[BUFFER_SIZE];
    char filename[50];

    do {
        printf("\n1. Add Line\n2. Insert Line\n3. Delete Line\n4. Print All\n5. Shrink Memory\n6. Save\n7. Load\n8. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        while(getchar() != '\n');

        switch(choice) {
            case 1:
                printf("Enter text: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                insertLine(lineCount, buffer);
                break;
            case 2:
                printf("Enter Index (1 to %d): ", lineCount + 1);
                scanf("%d", &idx);
                while(getchar() != '\n');
                printf("Enter text: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                insertLine(idx - 1, buffer);
                break;
            case 3:
                printf("Enter Index to delete (1 to %d): ", lineCount);
                scanf("%d", &idx);
                deleteLine(idx - 1);
                break;
            case 4:
                printAllLines();
                break;
            case 5:
                shrinkToFit();
                break;
            case 6:
                printf("Enter filename: ");
                scanf("%s", filename);
                saveToFile(filename);
                break;
            case 7:
                printf("Enter filename: ");
                scanf("%s", filename);
                loadFromFile(filename);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 8);

    freeAll();
    return 0;
}
