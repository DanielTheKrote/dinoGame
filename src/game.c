#include <ncurses/curses.h>
#include <stdlib.h>

#include "game.h"
#include "entity.h"

#define GROUND_SIZE 1
#define GROUND_CHAR 'W'
#define GROUND_OFFSET 2

#define OBSTACLE_SPAWN_POS_X    120
#define OBSTACLE_SPAWN_POS_Y    14
#define OBSTACLE_W              2
#define OBSTACLE_H              3

void draw_game_ground(WINDOW *window) 
{
    int max_h, max_w;
    getmaxyx(window, max_h, max_w);

    for (int y = max_h - GROUND_SIZE; y < max_h; y++)
        for (int x = 1; x < max_w - 1; x++)
            mvwaddch(window, y - GROUND_OFFSET, x, GROUND_CHAR);
}

t_entity *create_new_player() 
{
    t_entity *player = create_new_entity(PLAYER_SPAWNY, PLAYER_SPAWNX, 1, 1);
    return player;
}


t_obstacle_list *create_new_obstacle_list() 
{
    t_obstacle_list *obs = malloc(sizeof(t_obstacle_list));

    obs->next = NULL;
    obs->current = create_new_entity(
        OBSTACLE_SPAWN_POS_Y,
        OBSTACLE_SPAWN_POS_X,
        OBSTACLE_H,
        OBSTACLE_W
    );
    obs->current->dir.x = -1;
    obs->id = 0x69;

    return obs;
}

size_t sizeof_obstacle_list(t_obstacle_list *list_head) 
{
    t_obstacle_list *head; 
    size_t sizeof_list = 1;
    for (head = list_head; (head = head->next) != NULL; sizeof_list++);

    return sizeof_list;
}
