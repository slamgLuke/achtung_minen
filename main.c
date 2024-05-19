#include "achtung.h"
#include "term_manip.h"

static int run = 1;
static Gamedata game = {0};

void handle_malloc(int ret) {
    if (ret != 0) {
        printf("Closing due to grid allocation error\n");
        exit(1);
    } else {
        printf("Grid allocated\n");
    }
}

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
    // handle_malloc(malloc_grid(10, 10, 0.2));

    malloc_grid(&game, 15, 15, 0.2);
    init_grid(&game);
    printf("Grid initialized\n");

    // printf(FLUSH);
    print_grid(game);
    while (run) {
        handle_input(getchar());
    }
    printf("Closing...\n");

    return 0;
}
