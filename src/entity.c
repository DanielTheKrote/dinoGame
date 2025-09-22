#include <stdbool.h>

#include "entity.h"

t_vec2 create_new_vector2(int y, int x) {
    return (t_vec2)  {
        .x = x,
        .y = y,
    };
}


t_entity create_new_entity (int y, int x, int h, int w)
{
    return (t_entity) {
        .pos = create_new_vector2(y, x),
        .dir = create_new_vector2(0, 0),
        .h = h,
        .w = w,
    };
}

void apply_entity_dir(t_entity *e) 
{
    e->pos.x += e->dir.x;
    e->pos.y += e->dir.y;
}

bool check_aabb_collision(t_entity *e1, t_entity *e2) 
{    
    return (
        e1->pos.x < e2->pos.x + e2->w &&
        e1->pos.x + e1->w > e2->pos.x &&
        e1->pos.y < e2->pos.y + e2->h &&
        e1->pos.y + e1->h > e2->h
    );
}
