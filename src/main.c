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

    t_obstacle_list *obstacle_head = create_new_obstacle_list(10);
    
    size_t obstacle_count = 10;
    for (
        t_obstacle_list *head = obstacle_head; 
        head != NULL && obstacle_count > 0;
        --obstacle_count
    )
    {
        head->next = create_new_obstacle_list();
        head->next->current->pos.x = head->current->pos.x + 100;

        head = head->next;
    }

    for (;;) 
    {
        wclear(window);
        box(window, 0, 0);

        draw_game_ground(window);


        for (t_obstacle_list *head = obstacle_head; head != NULL;)
        {
            t_entity *current;
            if ((current = head->current) != NULL)
            {
                draw_block_to_window(
                    window,
                    current->pos.y,
                    current->pos.x,
                    current->h,
                    current->w,
                    '@'
                );
                apply_entity_dir(current); 
            
                if (current->pos.x < 0) 
                    current->pos.x = 120;

            }
            head = head->next;
        }

        mvwaddch(window, player->pos.y, player->pos.x, 'P');
       
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
