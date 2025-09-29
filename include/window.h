#ifndef WINDOW_H
#define WINDOW_H

void cast_curses();
void destroy_curses();
void draw_block_to_window(WINDOW *window, int y, int x, int h, int w, char ch);

void draw_player_score(WINDOW *window, unsigned int player_score);

void set_init_window(WINDOW *window);

WINDOW *create_new_centered_window();

#endif
