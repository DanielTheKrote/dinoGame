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

    player.dir.x = 1;

    for (;;) 
    {
        wclear(window);
        box(window, 0, 0);

        mvwaddch(window, player.pos.y, player.pos.x, 'P');
        draw_game_ground(window);

        apply_entity_dir(&player);
    
        wrefresh(window);

        usleep(SLEEPTIME);
    }
}
