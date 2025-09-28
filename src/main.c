#include <stdio.h> 
#include <time.h> 
#include <unistd.h> 
#include <ncurses/curses.h> 
#include <stdlib.h> 

#include "window.h"
#include "game.h"
#include "entity.h"

#define TARGET_FPS 24
#define SLEEPTIME 1000000 / TARGET_FPS

#define OBSTACLE_SPAWN_X 120
#define OBSTACLE_SPAWN_Y 14


int main(int argc, char **argv)
{
    cast_curses();
    
    WINDOW *window = create_new_centered_window();

    t_entity *player = create_new_player();

    // little hack 
    t_obstacle_list *obstacle_list = create_new_obstacle_node(100, 100);

    srand(time(NULL));

    while (1)
    {
        wclear(window);
        box(window, 0, 0);

        draw_game_ground(window);

        mvwaddch(window, player->pos.y, player->pos.x, 'P');

        t_obstacle_list *head = obstacle_list;
        size_t index = 0;
        while (head != NULL)
        {
            t_entity *obstacle = head->current;

            head = head->next;

            if (obstacle == NULL)
                continue;

            draw_block_to_window(
                window,
                obstacle->pos.y,
                obstacle->pos.x,
                obstacle->h,
                obstacle->w,
                '#'
            );

            apply_entity_dir(obstacle);

            if (obstacle->pos.x < 0 - obstacle->w)
            {

                if (index == 0)
                {
                    obstacle_list = obstacle_list->next;
                    continue;
                }

                remove_node_from_obstacle_list(obstacle_list, index);
                continue;
            }
            index++;
        }

        if ((rand() % (1000) + 0) % 19 == 0)
        {
            add_node_to_obstacle_list(
                obstacle_list, 
                create_new_obstacle_node(
                    OBSTACLE_SPAWN_Y,
                    OBSTACLE_SPAWN_X
                )
            );
        }

        if (player->pos.y > 15)
            player->pos.y = 15;
        
    
        switch (getch()) {
            case 'w':
                player->dir.y = -4;
                break;
            default:
                break;
        }

        player->dir.x = 0;
        if (player->dir.y <= 0)
            player->dir.y += 1;

        apply_entity_dir(player);
    
        wrefresh(window);

        usleep(SLEEPTIME);
    }
}
