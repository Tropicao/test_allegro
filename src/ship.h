#ifndef SHIP_H
#define SHIP_H

#include "allegro5/allegro.h"

#define PI                  3.14

#define NB_POS_IN_SPRITE    4
#define SHIP_RATIO          (1.0/10.0)
#define DELTA_Z_MAX         3
#define SHIP_FLOAT_SPEED    0.5
#define SHIP_SPEED          3

typedef enum
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
}Dir;

typedef struct
{
    ALLEGRO_BITMAP *sprite;
    int w;
    int h;
}Sprite;

typedef struct
{
    int current_z;
    int current_float_dir;
    float float_speed; /**< Number of complete animation cycle per second*/
    int frame_counter;
}Float_Dynamic;

typedef struct
{
    Sprite *sprite;
    int x;
    int y;
    Float_Dynamic anim;
    int is_moving;
    int speed; /**< Pixel per cycle */
    Dir current_dir;
}Ship;

Ship* create_new_ship(const char *path);
void print_ship_on_screen(Ship *ship);
void animate_ship(Ship *ship);
void move_ship(Ship *ship);




#endif
