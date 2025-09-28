#include <stdio.h> 

#include <unistd.h> 
#include <ncurses/curses.h> 
#include <stdlib.h> 

#include "window.h"
#include "game.h"
#include "entity.h"

#define TARGET_FPS 24
#define SLEEPTIME 1000000 / TARGET_FPS


int main(int argc, char **argv)
{
    cast_curses();
    
    WINDOW *window = create_new_centered_window();

    t_entity *player = create_new_player();

    t_obstacle_list *obstacle_list = create_new_obstacle_list();

    obstacle_list->current = create_new_entity(10, 20, 3, 3);

    obstacle_list->next = create_new_obstacle_list();

    obstacle_list->next->current = create_new_entity(10, 30, 3, 3);

    while (1)
    {
        wclear(window);
        box(window, 0, 0);

        draw_game_ground(window);

        mvwaddch(window, player->pos.y, player->pos.x, 'P');

        t_obstacle_list *head = obstacle_list;
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
