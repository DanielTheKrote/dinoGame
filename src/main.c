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

    t_entity obs = create_new_entity(14, 60, 3, 2);

    obs.dir.x = -2;


    for (;;) 
    {


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
       
        if (player.pos.y > 15)
            player.pos.y = 15;
        
    
        switch (getch()) {
            case 'w':
                player.dir.y = -4;
                break;
            default:
                break;
        }

        player.dir.x = 0;
        if (player.dir.y <= 0)
            player.dir.y += 1;

        apply_entity_dir(&player);
        apply_entity_dir(&obs);

        if (obs.pos.x < 0) {
            obs.pos.x = 120;
        }

        if (check_aabb_collision(&player, &obs)) 
        {
            obs.pos.x = 120;
        }
    
        wrefresh(window);

        usleep(SLEEPTIME);
    }
}
