#include "term_manip.h"

void set_term_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Turn off canonical mode and echo
    term.c_cc[VMIN] = 1; // Minimum number of characters to read
    term.c_cc[VTIME] = 0; // Timeout in deciseconds for read
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void num_color(int n) {
    switch(n) {
        case 1:
            printf(COLOR1);
            break;
        case 2:
            printf(COLOR2);
            break;
        case 3:
            printf(COLOR3);
            break;
        case 4:
            printf(COLOR4);
            break;
        case 5:
            printf(COLOR5);
            break;
        case 6:
            printf(COLOR6);
            break;
        case 7:
            printf(COLOR7);
            break;
        case 8:
            printf(COLOR8);
            break;
        default:
            printf(RESET);
            break;
    }
}
