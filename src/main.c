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

    player.dir.x = 1;

    for (;;) 
    {
        wclear(window);
        box(window, 0, 0);

        mvwaddch(window, player.pos.y, player.pos.x, 'P');

        for (int y = 0; y < obs.h; y++)
            for (int x = 0; x < obs.w; x++)
                mvwaddch(window, obs.pos.y + y, obs.pos.x + x, 'L');

        for (int y = 0; y < obs2.h; y++)
            for (int x = 0; x < obs2.w; x++)
                mvwaddch(window, obs2.pos.y + y, obs2.pos.x + x, 'L');

        draw_game_ground(window);

        apply_entity_dir(&player);

        if (
            check_aabb_collision(&player, &obs) ||
            check_aabb_collision(&player, &obs2) 
        ) 
        {
            player.dir.x *= -1;
        }
    
        wrefresh(window);

        usleep(SLEEPTIME);
    }
}
