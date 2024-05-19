#ifndef ACHTUNG_H
#define ACHTUNG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BITE_SIZE 8

#define MIN_SIZE 5
#define MAX_SIZE 20
#define MIN_DENSITY 0.15
#define MAX_DENSITY 0.85

#define MINE 256
#define FLAG_BIT 1 << (BITE_SIZE*sizeof(int)-1)

typedef struct {
    int** grid;
    int rows, cols;
    int mine_count;
} Gamedata;

void print_grid(Gamedata);

void init_grid(Gamedata*);
void lay_mines(Gamedata*);
void set_neighbors(Gamedata*);

int malloc_grid(Gamedata*, int rows, int cols, float density);
void free_grid(Gamedata*);


#endif
