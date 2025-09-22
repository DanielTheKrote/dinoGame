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

void apply_dir_to_entity(t_entity *e) 
{
    e->pos.x += e->dir.x;
    e->pos.y += e->dir.y;
}
