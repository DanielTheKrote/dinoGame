#ifndef ENTITY_H 
#define ENTITY_H 

typedef struct Vector2 {
    int x; 
    int y;
} t_vec2;

typedef struct Entity {
    t_vec2 pos;
    t_vec2 dir;
    int h;
    int w;
} t_entity;


void apply_entity_dir(t_entity *e);
t_entity *create_new_entity(int y, int x, int h, int w);
void destroy_entity(t_entity *entity);

bool check_aabb_collision(t_entity *e1, t_entity *e2);

#endif
