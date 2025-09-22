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
t_entity create_new_entity(int x, int y, int h, int w);

#endif
