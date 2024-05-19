#include "achtung.h"

void print_grid(Gamedata gamedata) {
    for (int i = 0; i < gamedata.rows; i++) {
        for (int j = 0; j < gamedata.cols; j++) {
            if (gamedata.grid[i][j] == MINE) {
                printf("X");
            } else {
                printf("%d", gamedata.grid[i][j]);
            }
        }
        printf("\n");
    }
}

void init_grid(Gamedata* gamedata) {
    for (int i = 0; i < gamedata->rows; i++) {
        for (int j = 0; j < gamedata->cols; j++) {
            gamedata->grid[i][j] = 0;
        }
    }
    printf("Zeroed data\n");
    srand(time(NULL));
    int n = gamedata->rows * gamedata->cols;
    int samples = gamedata->mine_count;

    int i, j = 0;
    while (samples > 0) {
        while (gamedata->grid[i][j] != 0) {
            j = (j+1) % gamedata->cols;
            i = (!j) ? (i+1) % gamedata->rows : i;
        }
        int p = rand() % n;
        if (!p) {
            gamedata->grid[i][j] = MINE;
            n--;
            samples--;
        } else {
            j = (j+1) % gamedata->cols;
            i = (!j) ? (i+1) % gamedata->rows : i;
        }
    }
}

void lay_mines(Gamedata* gamedata) {

}

void set_neighbors(Gamedata* gamedata) {
    for (int i = 0; i < gamedata->rows; i++) {
        for (int j = 0; j < gamedata->cols; j++) {
            if (gamedata->grid[i][j] == MINE) continue;
            int count = 0;
            for (int k = i-1; k <= i+1; k++) {
                for (int l = j-1; l <= j+1; l++) {
                    if (k < 0 || l < 0 || k >= gamedata->rows || l >= gamedata->cols) continue;
                    if (gamedata->grid[k][l] == MINE) count++;
                }
            }
            gamedata->grid[i][j] = count;
        }
    }
}

int malloc_grid(Gamedata* gamedata, int rows, int cols, float density) {
    gamedata->grid = (int**) malloc(rows*sizeof(int*));
    if (gamedata->grid == NULL) return 1;
    for (int i = 0; i < rows; i++) {
        gamedata->grid[i] = (int*) calloc(cols, sizeof(int));
        if (gamedata->grid[i] == NULL) {
            for (int ii = i-1; i >= 0; i--) {
                free(gamedata->grid[ii]);
            }
            free(gamedata->grid);
            gamedata->grid = NULL;
            return 1;
        }
    }
    gamedata->rows = rows;
    gamedata->cols = cols;
    gamedata->mine_count = (int) (density * rows * cols);

    return 0;
}

void free_grid(Gamedata* gamedata) {
    for (int i = 0; i < gamedata->rows; i++) {
        free(gamedata->grid[i]);
    }
    free(gamedata->grid);
}
