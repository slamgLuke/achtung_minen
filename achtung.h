#ifndef ACHTUNG_H
#define ACHTUNG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "term_manip.h"

#define BITE_SIZE 8

#define MIN_SIZE 8
#define MAX_SIZE 25
#define MIN_DENSITY 0.05
#define MAX_DENSITY 0.5

#define EMPTY 0
#define MINE 64
#define FLAG_BIT (unsigned int) (1 << (BITE_SIZE*sizeof(int)-1))
#define REVEAL_BIT (unsigned int) (1 << (BITE_SIZE*sizeof(int)-2))
#define VALUE_MASK (unsigned int) (REVEAL_BIT - 1)

#define MAX_ITER (int) 1e6

typedef struct {
    int** grid;
    int rows, cols;
    int mine_count;
} Gamedata;

typedef struct {
    int i, j;
} Point;

void print_grid(Gamedata, Point);
int check_win_condition(Gamedata);

int reveal(Gamedata*, Point);
void _reveal_all(Gamedata*);
void flag(Gamedata*, Point);

void set_neighbors(Gamedata*);
int init_grid(Gamedata*, Point);

int malloc_grid(Gamedata*, float);
void free_grid(Gamedata*);


#endif
