#include <stdio.h> 
#include <unistd.h> 
#include <ncurses/curses.h> 

#include "window.h"

int main(int argc, char **argv)
{
    cast_curses();

    
    WINDOW *window = create_new_centered_window();


    for (;;) 
    {
        wclear(window);
    
        box(window, 0, 0);

        wrefresh(window);

        sleep(1);
    }

    destroy_curses();
}
