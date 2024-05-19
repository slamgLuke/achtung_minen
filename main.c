#include "achtung.h"
#include "term_manip.h"

static int run = 1;

void handle_input(char c) {
    switch (c) {
        case 'q':   run = 0;    break;
    }
}

int main(int argc, char** argv) {
    // if (argc != 4) {
    //     printf("Usage: %s <rows> <cols> <density>\n", argv[0]);
    //     return 1;
    // }

    set_term_mode();
    // malloc_grid(atoi(argv[1]), atoi(argv[2]), atof(argv[3]));
    if (malloc_grid(10, 10, 0.2) != 0) return 1;
    printf("Grid allocated\n");
    printf("grid[1][2]=%d\n", *(*(grid+1)+2));

    init_grid();
    printf("Grid initialized\n");

    printf(FLUSH);
    print_grid();
    while (run) {
        handle_input(getchar());
    }
    printf("Closing...\n");


    return 0;
}
