#include <ncurses/curses.h>

#include "game.h"
#include "entity.h"

#define GROUND_SIZE 1
#define GROUND_CHAR 'W'
#define GROUND_OFFSET 2

void draw_game_ground(WINDOW *window) 
{
    int max_h, max_w;
    getmaxyx(window, max_h, max_w);

    for (int y = max_h - GROUND_SIZE; y < max_h; y++)
        for (int x = 1; x < max_w - 1; x++)
            mvwaddch(window, y - GROUND_OFFSET, x, GROUND_CHAR);
}

t_entity create_new_player() 
{
    t_entity player = create_new_entity(PLAYER_SPAWNY, PLAYER_SPAWNX, 1, 1);
    return player;
}
