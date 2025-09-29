#include <ncurses/curses.h>
#include <stdio.h>
#include <string.h>

#include "window.h"

void cast_curses()
{
    initscr();
    noecho();
    //cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

void destroy_curses() 
{
    endwin();
}

WINDOW *create_new_centered_window() 
{
    int max_h, max_w;
    getmaxyx(stdscr, max_h, max_w);
    
    int window_h = 20;
    int window_w = 80;

    WINDOW *window = newwin(
        window_h, 
        window_w,
        (max_h - window_h) / 2,
        (max_w - window_w) / 2 
    );

    return window;
}

void draw_block_to_window(WINDOW *window, int y, int x, int h, int w, char ch) 
{
    for (int j = 0; j < h; j++)
        for (int i = 0; i < w; i++)
            mvwaddch(window, y + j, x + i, ch);
}

void draw_player_score(WINDOW *window, unsigned int player_score) 
{
    char buf[10]; 
    sprintf(buf, "%d", player_score);

    int window_w = getmaxx(window);
    mvwprintw(window, 0, (window_w  - strlen(buf)) / 2, "%d", player_score);
}

void set_init_window(WINDOW *window)
{
    wclear(window);
    box(window, 0, 0);
    int window_w, window_h; 
    
    char *text = "Press any key to start the game!";

    getmaxyx(window, window_h, window_w);
    mvwprintw(
        window, 
        (window_h)  / 2,
        (window_w - strlen(text)) / 2, 
        "%s",
        text
    );
    wrefresh(window); 
}
