#ifndef ACHTUNG_H
#define ACHTUNG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 5
#define MAX_SIZE 20
#define MIN_DENSITY 0.15
#define MAX_DENSITY 0.85

#define MINE 256
#define FLAG_BIT 1 << (8*sizeof(int)-1)

static int** grid = NULL;
static int rows, cols, mine_count;

void print_grid();

void init_grid();
void lay_mines();
void set_neighbors();

int malloc_grid(int rows, int cols, float density);
void free_grid();


#endif
