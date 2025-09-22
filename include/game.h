#ifndef GAME_H
#define GAME_H 

#include "entity.h"

#define PLAYER_SPAWNX 8
#define PLAYER_SPAWNY 16

void draw_game_ground(WINDOW *window);
t_entity create_new_player();

#endif
