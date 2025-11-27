#include <stdio.h>
#include <stdbool.h>

#define N 5

struct Point {
    int r;
    int c;
};

struct Point path[N * N];
int pathIdx = 0;

int maze[N][N] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

int solution[N][N];

bool solve(int r, int c) {
    if (r == N - 1 && c == N - 1 && maze[r][c] == 0) {
        path[pathIdx].r = r;
        path[pathIdx].c = c;
        pathIdx++;
        solution[r][c] = 1;
        return true;
    }

    if (r >= 0 && c >= 0 && r < N && c < N && maze[r][c] == 0 && solution[r][c] == 0) {
        solution[r][c] = 1;
        path[pathIdx].r = r;
        path[pathIdx].c = c;
        pathIdx++;

        if (solve(r + 1, c)) return true;
        if (solve(r, c + 1)) return true;
        if (solve(r - 1, c)) return true;
        if (solve(r, c - 1)) return true;

        solution[r][c] = 0;
        pathIdx--;
        return false;
    }
    return false;
}

int main() {
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            solution[i][j] = 0;

    if (solve(0, 0)) {
        printf("Path Found! Coordinates:\n");
        for (int i = 0; i < pathIdx; i++) {
            printf("(%d, %d) ", path[i].r, path[i].c);
            if (i < pathIdx - 1) printf("-> ");
        }
        printf("\n");
        
        printf("\nVisual Path (1 is path):\n");
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                printf("%d ", solution[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("No path exists.\n");
    }

    return 0;
}