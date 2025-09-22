#include <ncurses/curses.h>

#include "game.h"

#define GROUND_SIZE 1
#define GROUND_CHAR 'W'
#define GROUND_OFFSET 2

void draw_game_ground(WINDOW *window) 
{
    int max_h, max_w;
    getmaxyx(window, max_h, max_w);

    for (int y = max_h - GROUND_SIZE; y < max_h; y++)
        for (int x = 0; x < max_w; x++)
            mvwaddch(window, y - GROUND_OFFSET, x, GROUND_CHAR);
}
