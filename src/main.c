#include <stdio.h> 
#include <unistd.h> 
#include <ncurses/curses.h> 

#include "window.h"
#include "game.h"
#include "entity.h"


int main(int argc, char **argv)
{
    cast_curses();

    
    WINDOW *window = create_new_centered_window();

    t_entity player = create_new_player();

    for (;;) 
    {
        wclear(window);
        box(window, 0, 0);

        mvwaddch(window, player.pos.y, player.pos.x, 'P');
        draw_game_ground(window);
    

        wrefresh(window);

        sleep(1);
    }

    destroy_curses();
}
