#ifndef WINDOW_H
#define WINDOW_H

void cast_curses();
void destroy_curses();
void draw_block_to_window(WINDOW *window, int y, int x, int h, int w, char ch);

WINDOW *create_new_centered_window();

#endif
