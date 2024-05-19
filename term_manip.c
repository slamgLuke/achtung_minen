#include "term_manip.h"

void set_term_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Turn off canonical mode and echo
    term.c_cc[VMIN] = 1; // Minimum number of characters to read
    term.c_cc[VTIME] = 0; // Timeout in deciseconds for read
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
