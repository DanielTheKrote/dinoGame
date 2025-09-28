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
} t_obstacle_list;

//t_obstacle_list *create_new_obstacle_list();
t_obstacle_list *create_new_obstacle_node(t_entity *obstacle);

void add_node_to_obstacle_list(
    t_obstacle_list *next, 
    t_obstacle_list *list_head
);

#endif
