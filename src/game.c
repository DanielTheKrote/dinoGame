#include <ncurses/curses.h>
#include <stdlib.h>

#include "game.h"
#include "entity.h"

#define GROUND_SIZE 1
#define GROUND_CHAR 'W'
#define GROUND_OFFSET 2

#define OBSTACLE_SPAWN_POS_X    120
#define OBSTACLE_SPAWN_POS_Y    14
#define OBSTACLE_W              2
#define OBSTACLE_H              3

void draw_game_ground(WINDOW *window) 
{
    int max_h, max_w;
    getmaxyx(window, max_h, max_w);

    for (int y = max_h - GROUND_SIZE; y < max_h; y++)
        for (int x = 1; x < max_w - 1; x++)
            mvwaddch(window, y - GROUND_OFFSET, x, GROUND_CHAR);
}

t_entity *create_new_player() 
{
    t_entity *player = create_new_entity(PLAYER_SPAWNY, PLAYER_SPAWNX, 1, 1);
    return player;
}


t_obstacle_list *create_new_obstacle_list()
{
    t_obstacle_list *list = malloc(sizeof(t_obstacle_list));
    list->current = NULL;
    list->next = NULL;
    return list;
}

t_obstacle_list *create_new_obstacle_node(int y, int x) 
{
    t_entity *obstacle = create_new_entity(y, x, OBSTACLE_H, OBSTACLE_W);
    
    obstacle->dir.x = -1;

    t_obstacle_list *node = create_new_obstacle_list();
    node->current = obstacle;
    return node;
}

void destroy_obstacle_node(t_obstacle_list *node)
{
    if (node->current) 
        destroy_entity(node->current);

    free(node);
}


void add_node_to_obstacle_list(
    t_obstacle_list *list_head,
    t_obstacle_list *next
)
{
    t_obstacle_list *head = list_head;
    while (head->next != NULL)
        head = head->next;

    head->next = next;
}

size_t get_obstacle_list_size(t_obstacle_list *list_head)
{
    t_obstacle_list *head = list_head;
    size_t count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

void remove_node_from_obstacle_list(
    t_obstacle_list *list_head,
    size_t node_index
)
{
    size_t list_size = get_obstacle_list_size(list_head);

    if (node_index < 0 || node_index >= list_size)
        return;


    t_obstacle_list *last = list_head;
    t_obstacle_list *current = list_head;

    while (current != NULL)
    {
    
        if ((node_index--) == 0) // target node 
        { 
            last->next = current->next;
            destroy_obstacle_node(current);
            return;
        }

        last = current;
        current = current->next;            
    }
}
