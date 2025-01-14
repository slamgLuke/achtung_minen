#include "achtung.h"

void print_grid(Gamedata gamedata, Point selected) {
    printf(WALL_COLOR "+");
    for (int i = 0; i < gamedata.cols*3; i++) {
        printf("-");
    }
    puts("+");

    for (int i = 0; i < gamedata.rows; i++) {
        printf(WALL_COLOR "|");
        for (int j = 0; j < gamedata.cols; j++) {
            if (i == selected.i && j == selected.j) {
                printf(SELECT_COLOR ">");
            } else {
                printf(" ");
            }
            if (gamedata.grid[i][j] & REVEAL_BIT) {
                if (gamedata.grid[i][j] == (MINE | REVEAL_BIT)) {
                    printf(MINE_COLOR "X");
                } else if (gamedata.grid[i][j] == (MINE | FLAG_BIT | REVEAL_BIT)) {
                    printf(FLAG_COLOR "X");
                } else if (gamedata.grid[i][j] == (EMPTY | REVEAL_BIT)) {
                    printf(" ");
                } else if (gamedata.grid[i][j] & FLAG_BIT) {
                    printf(MINE_COLOR "%d", gamedata.grid[i][j] & VALUE_MASK);
                } else {
                    num_color(gamedata.grid[i][j] & VALUE_MASK);
                    printf("%d", gamedata.grid[i][j] & VALUE_MASK);
                }
            } else if (gamedata.grid[i][j] & FLAG_BIT) {
                printf(FLAG_COLOR "F");
            } else {
                if (i % 2 == 0) printf(BASIC "\u2588");
                else printf(BASIC "\u2593");
                // if (gamedata.grid[i][j] & MINE) {
                //     printf(" * ");
                // } else {
                //     printf(" %d ", gamedata.grid[i][j] & VALUE_MASK);
                // }
            }
            if (i == selected.i && j == selected.j) {
                printf(SELECT_COLOR "<");
            } else {
                printf(" ");
            }
        }
        puts(WALL_COLOR "|");
    }

    printf(WALL_COLOR "+");
    for (int i = 0; i < gamedata.cols*3; i++) {
        printf("-");
    }
    puts("+");
}

int check_win_condition(Gamedata gamedata) {
    int revealed_count = 0;
    for (int i = 0; i < gamedata.rows; i++) {
        for (int j = 0; j < gamedata.cols; j++) {
            if (gamedata.grid[i][j] == (MINE | REVEAL_BIT)) return 0;
            if (gamedata.grid[i][j] & REVEAL_BIT) revealed_count++;
        }
    }
    int flagged_mine_count = 0;
    for (int i = 0; i < gamedata.rows; i++) {
        for (int j = 0; j < gamedata.cols; j++) {
            if (gamedata.grid[i][j] == (MINE | FLAG_BIT)) flagged_mine_count++;
        }
    }
    int win = (revealed_count + flagged_mine_count) == (gamedata.rows * gamedata.cols);
    return win;
}

int reveal(Gamedata* gamedata, Point p) {
    if (gamedata->grid[p.i][p.j] & FLAG_BIT) return 0;
    if (gamedata->grid[p.i][p.j] == MINE) {
        _reveal_all(gamedata);
        return 1;
    }

    gamedata->grid[p.i][p.j] |= REVEAL_BIT;
    if ((gamedata->grid[p.i][p.j] & VALUE_MASK) != EMPTY) return 0;

    for (int k = p.i-1; k <= p.i+1; k++) {
        for (int l = p.j-1; l <= p.j+1; l++) {
            if (k < 0 || l < 0 || k >= gamedata->rows || l >= gamedata->cols) continue;
            if (gamedata->grid[k][l] & REVEAL_BIT) continue;
            if (gamedata->grid[k][l] & FLAG_BIT) continue;
            // if (gamedata->grid[k][l] & MINE) continue;
            if (gamedata->grid[k][l] == EMPTY) {
                Point next = {k, l};
                reveal(gamedata, next);
            } else {
                gamedata->grid[k][l] |= REVEAL_BIT;
            }
        }
    }
    return 0;
}

void _reveal_all(Gamedata* gamedata) {
    for (int i = 0; i < gamedata->rows; i++) {
        for (int j = 0; j < gamedata->cols; j++) {
            gamedata->grid[i][j] |= REVEAL_BIT;
        }
    }
}

void flag(Gamedata* gamedata, Point p) {
    if (gamedata->grid[p.i][p.j] & REVEAL_BIT) return;
    gamedata->grid[p.i][p.j] ^= FLAG_BIT;
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

int init_grid(Gamedata* gamedata, Point p) {
    for (int i = 0; i < gamedata->rows; i++) {
        memset(gamedata->grid[i], EMPTY, gamedata->cols*sizeof(int));
    }
    // mark first cell and neighbors as not mines
    for (int k = p.i-1; k <= p.i+1; k++) {
        for (int l = p.j-1; l <= p.j+1; l++) {
            if (k < 0 || l < 0 || k >= gamedata->rows || l >= gamedata->cols) continue;
            gamedata->grid[k][l] = 8; // arbitrary const
        }
    }

    // place mines randomly
    srand(time(NULL));
    int n = gamedata->rows * gamedata->cols - 1;
    int remaining = gamedata->mine_count;

    int iter = 0;
    int i = 0, j = 0;
    while (remaining > 0 && iter < MAX_ITER) {
        while (gamedata->grid[i][j] != EMPTY && iter < MAX_ITER) {
            j = (j+1) % gamedata->cols;
            i = (!j) ? (i+1) % gamedata->rows : i;
            iter++;
        }
        int p = rand() % n; // p = 1/n
        if (!p) {
            gamedata->grid[i][j] = MINE;
            n--;
            remaining--;
        } else {
            j = (j+1) % gamedata->cols;
            i = (!j) ? (i+1) % gamedata->rows : i;
        }
        iter++;
    }
    if (remaining > 0) return 1;
    else return 0;
}


int malloc_grid(Gamedata* gamedata, float density) {
    gamedata->grid = (int**) malloc(gamedata->rows*sizeof(int*));
    if (gamedata->grid == NULL) return 1;
    for (int i = 0; i < gamedata->rows; i++) {
        gamedata->grid[i] = (int*) malloc(gamedata->cols*sizeof(int));
        if (gamedata->grid[i] == NULL) {
            for (int ii = i-1; i >= 0; i--) {
                free(gamedata->grid[ii]);
            }
            free(gamedata->grid);
            gamedata->grid = NULL;
            return 1;
        }
    }
    gamedata->mine_count = (int) (density * gamedata->rows * gamedata->cols);
    return 0;
}

void free_grid(Gamedata* gamedata) {
    for (int i = 0; i < gamedata->rows; i++) {
        free(gamedata->grid[i]);
    }
    free(gamedata->grid);
    gamedata->grid = NULL;
    gamedata->rows = 0;
    gamedata->cols = 0;
    gamedata->mine_count = 0;
}
