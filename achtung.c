#include "achtung.h"

void print_grid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == MINE) {
                printf("X");
            } else {
                printf("%d", grid[i][j]);
            }
        }
        printf("\n");
    }
}

void init_grid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
        }
    }
    lay_mines();
}

void lay_mines() {
    srand(time(NULL));
    int n = rows * cols;
    int samples = mine_count;

    int i, j = 0;
    while (samples > 0) {
        while (grid[i][j] != 0) {
            j = (j+1) % cols;
            i = (!j) ? (i+1) % rows : i;
        }
        int p = rand() % n;
        if (!p) {
            grid[i][j] = MINE;
            n--;
            samples--;
        } else {
            j = (j+1) % cols;
            i = (!j) ? (i+1) % rows : i;
        }
    }
}

void set_neighbors() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == MINE) continue;
            int count = 0;
            for (int k = i-1; k <= i+1; k++) {
                for (int l = j-1; l <= j+1; l++) {
                    if (k < 0 || l < 0 || k >= rows || l >= cols) continue;
                    if (grid[k][l] == MINE) count++;
                }
            }
            grid[i][j] = count;
        }
    }
}

int malloc_grid(int _rows, int _cols, float density) {
    rows = _rows;
    cols = _cols;
    mine_count = (int) (rows * cols * density);

    grid = (int**) malloc(rows * sizeof(int*));
    if (grid == NULL) {
        printf("Failed to allocate memory for grid\n");
        free(grid);
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        grid[i] = (int*) calloc(cols, sizeof(int));
        if (grid[i] == NULL) {
            printf("Failed to allocate memory for grid row\n");
            for (int j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            free(grid);
            return 1;
        }
    }

    return 0;
}

void free_grid() {
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
    free(grid);
}
