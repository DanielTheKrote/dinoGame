#include <stdio.h> 
#include <unistd.h> 
#include <ncurses/curses.h> 

#include "window.h"
#include "game.h"

int main(int argc, char **argv)
{
    cast_curses();

    
    WINDOW *window = create_new_centered_window();

    for (;;) 
    {
        wclear(window);

        draw_game_ground(window);
    
        box(window, 0, 0);

        wrefresh(window);

        sleep(1);
    }

    destroy_curses();
}
