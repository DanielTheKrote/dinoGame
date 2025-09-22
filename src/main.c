#include <stdio.h> 
#include <ncurses/curses.h> 

#include "window.h"

int main(int argc, char **argv)
{
    cast_curses();
    destroy_curses();
}
