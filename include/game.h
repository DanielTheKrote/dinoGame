#ifndef GAME_H
#define GAME_H 

#include "entity.h"

#define PLAYER_SPAWNX 8
#define PLAYER_SPAWNY 16

void draw_game_ground(WINDOW *window);
t_entity *create_new_player();

typedef struct game_obstacles
{
    t_entity *current;
    struct game_obstacles *next;
    size_t  id;
} t_obstacle_list;


t_obstacle_list *create_new_obstacle_list();
size_t sizeof_obstacle_list(t_obstacle_list *list_head);

#endif
