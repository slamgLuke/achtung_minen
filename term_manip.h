#ifndef TERM_MANIP_H
#define TERM_MANIP_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>


#define FLUSH "\033[H\033[J"

#define TL "\033[1;1H"
#define BL "\033[1;80H"
#define TR "\033[24;1H"
#define BR "\033[24;80H"

#define RESET "\033[0m"
#define MINE_COLOR "\033[38;5;232m"
#define FLAG_COLOR "\033[38;5;196m"
#define WALL_COLOR "\033[38;5;50m"
#define SELECT_COLOR "\033[38;5;190m"

#define COLOR1 "\033[38;5;27m" // bright blue
#define COLOR2 "\033[38;5;28m" // forest green
#define COLOR3 "\033[38;5;46m" // bright red
#define COLOR4 "\033[38;5;20m" // dark blue
#define COLOR5 "\033[38;5;142m" // wine
#define COLOR6 "\033[38;5;79m" // teal
#define COLOR7 "\033[38;5;93m" // purple
#define COLOR8 "\033[38;5;1m" // black

#define BACKGROUND "\033[48;5;0m"
#define BASIC "\033[38;5;255m" // white

void set_term_mode();
void num_color(int);


#endif
