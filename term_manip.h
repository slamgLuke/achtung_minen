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
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"


void set_term_mode();


#endif
