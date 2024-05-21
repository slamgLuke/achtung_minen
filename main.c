#include "achtung.h"
#include "term_manip.h"

#define MAX_PARAM_READ 5


static int run = 1;
static int win = 0;
static int quit = 0;
static Gamedata game = {0};
static float density;
static Point selected = {0, 0};
static int has_selected_first = 0;

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
    while (!has_selected_first && run) {
        printf(FLUSH);
        print_grid(game, selected);
        printf("Select a cell to begin!\n");
        handle_input(getchar());
    }
    if (!run) goto end_game;

    // form grid
    handle_init(init_grid(&game, selected));
    set_neighbors(&game);
    reveal(&game, selected);
    printf(FLUSH);
    print_grid(game, selected);

    // main loop
    while (run && !win) {
        handle_input(getchar());
        win = check_win_condition(game);
        printf(FLUSH);
        print_grid(game, selected);
    }

    if (quit) goto end_game;
    if (win) {
        printf("You win!\n");
    } else {
        printf("You lose!\n");
    }

end_game:
    printf("Closing...\n");
    free_grid(&game);

    return 0;
}

void handle_input(char c) {
    switch (c) {
        case 'Q':
            run = 0;
            quit = 1;
            break;
        case 'f':
            if (has_selected_first) {
                flag(&game, selected);
            }
            break;
        case 'w':
            selected.i = (selected.i - 1 + game.rows) % game.rows;
            break;
        case 's':
            selected.i = (selected.i + 1) % game.rows;
            break;
        case 'a':
            selected.j = (selected.j - 1 + game.cols) % game.cols;
            break;
        case 'd':
            selected.j = (selected.j + 1) % game.cols;
            break;
        case ' ':
            if (!has_selected_first) {
                has_selected_first = 1;
            } else {
                run = !reveal(&game, selected);
            }
            break;
        default:
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
        printf("Closing due to parameter error\n");
        exit(1);
    }
    if (density < MIN_DENSITY || density > MAX_DENSITY) {
        printf("Invalid density\n");
        printf("Density must be between %f and %f\n", MIN_DENSITY, MAX_DENSITY);
        printf("Closing due to parameter error\n");
        exit(1);
    }
}

void read_params() {
    int times_read = 0;
    while (times_read <= MAX_PARAM_READ) {
        printf("Enter number of rows, columns and mine density: ");
        scanf("%d %d %f", &game.rows, &game.cols, &density);
        if (game.rows < MIN_SIZE || game.rows > MAX_SIZE ||
            game.cols < MIN_SIZE || game.cols > MAX_SIZE) {
            printf("Invalid dimensions\n");
            printf("Dimensions must be between %d and %d\n", MIN_SIZE, MAX_SIZE);
            times_read++;
        } else if (density < MIN_DENSITY || density > MAX_DENSITY) {
            printf("Invalid density\n");
            printf("Density must be between %f and %f\n", MIN_DENSITY, MAX_DENSITY);
            times_read++;
        } else {
            break;
        }
    }
    if (times_read > MAX_PARAM_READ) {
        printf("Too many invalid inputs\n");
        printf("Closing due to input error\n");
        exit(1);
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
