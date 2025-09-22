#include <ncurses/curses.h>
#include <stdio.h>

#include "window.h"

void cast_curses()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

void destroy_curses() 
{
    endwin();
}
