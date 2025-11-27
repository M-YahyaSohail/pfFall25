#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int popularity;
    int lastAccessTime; 
};

struct Book shelf[100]; // Assuming max capacity is reasonable
int currentCount = 0;
int capacity = 0;
int globalTime = 0; 

int findBookIndex(int id) {
    for (int i = 0; i < currentCount; i++) {
        if (shelf[i].id == id) {
            return i;
        }
    }
    return -1;
}

void addBook(int id, int pop) {
    globalTime++;
    int idx = findBookIndex(id);

    if (idx != -1) {
        shelf[idx].popularity = pop;
        shelf[idx].lastAccessTime = globalTime;
        return;
    }

    if (currentCount < capacity) {
        shelf[currentCount].id = id;
        shelf[currentCount].popularity = pop;
        shelf[currentCount].lastAccessTime = globalTime;
        currentCount++;
    } 
    else {
        int lruIndex = 0;
        for (int i = 1; i < currentCount; i++) {
            if (shelf[i].lastAccessTime < shelf[lruIndex].lastAccessTime) {
                lruIndex = i;
            }
        }
        
        shelf[lruIndex].id = id;
        shelf[lruIndex].popularity = pop;
        shelf[lruIndex].lastAccessTime = globalTime;
    }
}

void accessBook(int id) {
    globalTime++;
    int idx = findBookIndex(id);

    if (idx != -1) {
        shelf[idx].lastAccessTime = globalTime;
        printf("%d\n", shelf[idx].popularity);
    } else {
        printf("-1\n");
    }
}

int main() {
    int Q;
    scanf("%d %d", &capacity, &Q);

    char command[10];
    int id, pop;

    for (int i = 0; i < Q; i++) {
        scanf("%s", command);
        if (strcmp(command, "ADD") == 0) {
            scanf("%d %d", &id, &pop);
            addBook(id, pop);
        } else if (strcmp(command, "ACCESS") == 0) {
            scanf("%d", &id);
            accessBook(id);
        }
    }
    return 0;
}
