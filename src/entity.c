#include <stdbool.h>
#include <stdlib.h>

#include "entity.h"

t_vec2 create_new_vector2(int y, int x) {
    return (t_vec2)  {
        .x = x,
        .y = y,
    };
}


t_entity *create_new_entity(int y, int x, int h, int w)
{
    t_entity *new_entity = malloc(sizeof(t_entity));
    new_entity->pos = create_new_vector2(y, x);
    new_entity->dir = create_new_vector2(0, 0);
    new_entity->h = h;
    new_entity->w = w;
    return new_entity;
}

void apply_entity_dir(t_entity *e) 
{
    e->pos.x += e->dir.x;
    e->pos.y += e->dir.y;
}

bool check_aabb_collision(t_entity *entity_a, t_entity *entity_b) 
{    
    int left_a = entity_a->pos.x;
    int right_a = entity_a->pos.x + entity_a->w;
    int top_a = entity_a->pos.y;
    int bottom_a = entity_a->pos.y + entity_a->h;


    int left_b = entity_b->pos.x;
    int right_b = entity_b->pos.x + entity_b->w;
    int top_b = entity_b->pos.y;
    int bottom_b = entity_b->pos.y + entity_b->h;

   return !( 
        bottom_a <= top_b   ||
        top_a >= bottom_b   ||
        right_a <= left_b   || 
        left_a  >= right_b  
    );
}
