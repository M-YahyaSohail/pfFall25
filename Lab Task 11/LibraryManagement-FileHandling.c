#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS_PER_MEMBER 3
#define FILE_BOOKS "books.dat"
#define FILE_MEMBERS "members.dat"

struct Book {
    int id;
    char title[50];
    char author[50];
    char isbn[20];
    int year;
    int isAvailable; 
};

struct Member {
    int id;
    char name[50];
    char contact[20];
    int borrowedBookIDs[MAX_BOOKS_PER_MEMBER];
    int borrowCount;
};

struct Book library[100];
int bookCount = 0;

struct Member members[100];
int memberCount = 0;

void saveData() {
    FILE *fp = fopen(FILE_BOOKS, "wb");
    if (fp) {
        fwrite(&bookCount, sizeof(int), 1, fp);
        fwrite(library, sizeof(struct Book), bookCount, fp);
        fclose(fp);
    }
    
    fp = fopen(FILE_MEMBERS, "wb");
    if (fp) {
        fwrite(&memberCount, sizeof(int), 1, fp);
        fwrite(members, sizeof(struct Member), memberCount, fp);
        fclose(fp);
    }
    printf("Data saved successfully.\n");
}

void loadData() {
    FILE *fp = fopen(FILE_BOOKS, "rb");
    if (fp) {
        fread(&bookCount, sizeof(int), 1, fp);
        fread(library, sizeof(struct Book), bookCount, fp);
        fclose(fp);
    }

    fp = fopen(FILE_MEMBERS, "rb");
    if (fp) {
        fread(&memberCount, sizeof(int), 1, fp);
        fread(members, sizeof(struct Member), memberCount, fp);
        fclose(fp);
    }
}

void addBook() {
    struct Book b;
    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Title: ");
    scanf(" %[^\n]s", b.title);
    printf("Enter Author: ");
    scanf(" %[^\n]s", b.author);
    printf("Enter ISBN: ");
    scanf("%s", b.isbn);
    printf("Enter Year: ");
    scanf("%d", &b.year);
    b.isAvailable = 1;

    library[bookCount++] = b;
    saveData();
}

void addMember() {
    struct Member m;
    printf("Enter Member ID: ");
    scanf("%d", &m.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", m.name);
    printf("Enter Contact: ");
    scanf("%s", m.contact);
    m.borrowCount = 0;
    for(int i=0; i<MAX_BOOKS_PER_MEMBER; i++) m.borrowedBookIDs[i] = 0;

    members[memberCount++] = m;
    saveData();
}

void issueBook() {
    int mID, bID, mIdx = -1, bIdx = -1;
    printf("Enter Member ID: ");
    scanf("%d", &mID);
    printf("Enter Book ID: ");
    scanf("%d", &bID);

    for(int i=0; i<memberCount; i++) if(members[i].id == mID) mIdx = i;
    for(int i=0; i<bookCount; i++) if(library[i].id == bID) bIdx = i;

    if (mIdx != -1 && bIdx != -1) {
        if (library[bIdx].isAvailable == 0) {
            printf("Book is currently borrowed.\n");
            return;
        }
        if (members[mIdx].borrowCount >= MAX_BOOKS_PER_MEMBER) {
            printf("Member has reached borrow limit.\n");
            return;
        }

        library[bIdx].isAvailable = 0;
        members[mIdx].borrowedBookIDs[members[mIdx].borrowCount++] = bID;
        printf("Book issued successfully.\n");
        saveData();
    } else {
        printf("Invalid Member or Book ID.\n");
    }
}

void returnBook() {
    int mID, bID, mIdx = -1, bIdx = -1;
    printf("Enter Member ID: ");
    scanf("%d", &mID);
    printf("Enter Book ID: ");
    scanf("%d", &bID);

    for(int i=0; i<memberCount; i++) if(members[i].id == mID) mIdx = i;
    for(int i=0; i<bookCount; i++) if(library[i].id == bID) bIdx = i;

    if (mIdx != -1 && bIdx != -1) {
        int found = 0;
        for (int i=0; i < members[mIdx].borrowCount; i++) {
            if (members[mIdx].borrowedBookIDs[i] == bID) {
                found = 1;
                for (int j=i; j < members[mIdx].borrowCount - 1; j++) {
                    members[mIdx].borrowedBookIDs[j] = members[mIdx].borrowedBookIDs[j+1];
                }
                members[mIdx].borrowCount--;
                break;
            }
        }
        if (found) {
            library[bIdx].isAvailable = 1;
            printf("Book returned successfully.\n");
            saveData();
        } else {
            printf("This member does not have this book.\n");
        }
    } else {
        printf("Invalid ID.\n");
    }
}

int main() {
    loadData();
    int choice;
    do {
        printf("\n1. Add Book\n2. Add Member\n3. Issue Book\n4. Return Book\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: addBook(); break;
            case 2: addMember(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
            case 5: saveData(); break;
        }
    } while (choice != 5);
    return 0;
}