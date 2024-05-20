#include "achtung.h"
#include "term_manip.h"

static int run = 1;
static Gamedata game = {0};
static float density;

void handle_input(char);
void read_args(int, char*[]);
void read_params();
void handle_malloc(int);
void handle_init(int);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        read_args(argc, argv);
    } else {
        read_params();
    }
    set_term_mode();
    handle_malloc(malloc_grid(&game, density));

    // first reveal
    Point first = {0, 0};

    // grid layout
    handle_init(init_grid(&game, first));
    set_neighbors(&game);
    reveal(&game, first);

    printf(FLUSH);
    print_grid(game);
    while (run) {
        handle_input(getchar());
        printf(FLUSH);
        print_grid(game);
    }

    printf("Closing...\n");
    free_grid(&game);

    return 0;
}

void handle_input(char c) {
    switch (c) {
        case 'Q':
            run = 0;
            break;
    }
}

void read_args(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Invalid number of arguments\n");
        printf("Usage: %s <rows> <cols> <density>\n", argv[0]);
        exit(1);
    }
    game.rows = atoi(argv[1]);
    game.cols = atoi(argv[2]);
    density = atof(argv[3]);
    if (game.rows < MIN_SIZE || game.rows > MAX_SIZE || game.cols < MIN_SIZE ||
        game.cols > MAX_SIZE) {
        printf("Invalid dimensions\n");
        printf("Dimensions must be between %d and %d\n", MIN_SIZE, MAX_SIZE);
        exit(1);
    }
    if (density < MIN_DENSITY || density > MAX_DENSITY) {
        printf("Invalid density\n");
        printf("Density must be between %f and %f\n", MIN_DENSITY, MAX_DENSITY);
        exit(1);
    }
}

void read_params() {
    while (1) {
        printf("Enter number of rows, columns and mine density: ");
        scanf("%d %d %f", &game.rows, &game.cols, &density);
        if (game.rows < MIN_SIZE || game.rows > MAX_SIZE ||
            game.cols < MIN_SIZE || game.cols > MAX_SIZE) {
            printf("Invalid dimensions\n");
            printf("Dimensions must be between %d and %d\n", MIN_SIZE,
                   MAX_SIZE);
        } else if (density < MIN_DENSITY || density > MAX_DENSITY) {
            printf("Invalid density\n");
            printf("Density must be between %f and %f\n", MIN_DENSITY,
                   MAX_DENSITY);
        } else {
            break;
        }
    }
}

void handle_malloc(int ret) {
    if (ret != 0) {
        printf("Closing due to allocation error\n");
        exit(1);
    }
}

void handle_init(int ret) {
    if (ret != 0) {
        printf("Maximum number of iterations reached: %d\n", MAX_ITER);
        printf("Closing due to initialization error\n");
        exit(1);
    }
}
