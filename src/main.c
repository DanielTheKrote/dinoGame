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

#define OBSTACLE_SPAWN_X 100
#define OBSTACLE_SPAWN_Y 14


t_entity *player; 
t_obstacle_list *obstacle_list; 
time_t last_spawned_time;

void restart_game() 
{
    player = create_new_player();

    // little hack 
    obstacle_list = create_new_obstacle_node(100, 100);
    obstacle_list->current->dir.x = 0;

    time(&last_spawned_time);
}


int main(int argc, char **argv)
{
    cast_curses();

    restart_game();
    
    WINDOW *window = create_new_centered_window();


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

            if (check_aabb_collision(player, obstacle))
            {
                restart_game();
                continue;
            }

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


        time_t current_time;
        time(&current_time);

        bool enought_time = current_time - last_spawned_time > 1;

        if ((rand() % 30) == 3 && enought_time)
        {
            add_node_to_obstacle_list(
                obstacle_list, 
                create_new_obstacle_node(
                    OBSTACLE_SPAWN_Y,
                    OBSTACLE_SPAWN_X
                )
            );
            last_spawned_time = current_time;
        }


        bool is_player_on_ground = false;
        if (player->pos.y > 15)
        {
            player->pos.y = 15;
            is_player_on_ground = true;
        }
        
    
        switch (getch()) 
        {
            case 'w':
                if (is_player_on_ground)
                    player->dir.y = -4;
                break;
            default:
                break;
        }

        if (player->dir.y <= 0)
            player->dir.y += 1;

        apply_entity_dir(player);
    
        wrefresh(window);

        usleep(SLEEPTIME);
    }
}
