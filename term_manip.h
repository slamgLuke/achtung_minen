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


void set_term_mode();


#endif
