#include <stdio.h> 
#include <unistd.h> 
#include <ncurses/curses.h> 

#include "window.h"
#include "game.h"
#include "entity.h"

#define TARGET_FPS 24
#define SLEEPTIME 1000000 / TARGET_FPS

int main(int argc, char **argv)
{
    cast_curses();
    
    WINDOW *window = create_new_centered_window();

    t_entity player = create_new_player();

    t_entity obs = create_new_entity(14, 60, 3, 3);
    t_entity obs2 = create_new_entity(14, 1, 3, 3);


    for (;;) 
    {

        player.dir.x = 0;

        wclear(window);
        box(window, 0, 0);

        draw_game_ground(window);
        mvwaddch(window, player.pos.y, player.pos.x, 'P');

        draw_block_to_window(
            window, 
            obs.pos.y,
            obs.pos.x,
            obs.h,
            obs.w, 
            'L'
        );

        draw_block_to_window(
            window, 
            obs2.pos.y,
            obs2.pos.x,
            obs2.h,
            obs2.w, 
            'L'
        );
        
    
        switch (getch()) {
            case 'a':
                player.dir.x = -1;
                break;
            case 'd':
                player.dir.x = 1;
                break;
            default:
                break;
        }

        apply_entity_dir(&player);

        if (
            check_aabb_collision(&player, &obs) ||
            check_aabb_collision(&player, &obs2) 
        ) 
        {
            player.pos.x = 7;
        }
    
        wrefresh(window);

        usleep(SLEEPTIME);
    }
}
