#include "ship.h"
#include <stdio.h>
#include "screen.h"
#include <math.h>

Ship* create_new_ship(const char *path)
{
    Ship *result = NULL;
    int i=0;
    ALLEGRO_BITMAP *buffer = NULL;
    result = calloc(1, sizeof(Ship));
    if(result != NULL)
    {
        result->sprite=calloc(NB_POS_IN_SPRITE, sizeof(Sprite));
        if(result->sprite != NULL)
        {
            buffer = al_load_bitmap(path);
            if(buffer == NULL)
            {
                fprintf(stderr, "Cannot open sprite file\n");
                return NULL;
            }
            for (i=0; i<NB_POS_IN_SPRITE; i++)
            {
                result->sprite[i].w = al_get_bitmap_width(buffer) * SHIP_RATIO;
                result->sprite[i].h = al_get_bitmap_height(buffer) * SHIP_RATIO;
                result->sprite[i].sprite = al_create_bitmap(result->sprite[i].w, result->sprite[i].h);
                al_set_target_bitmap(result->sprite[i].sprite);
                al_draw_scaled_rotated_bitmap(buffer,al_get_bitmap_width(buffer)/2, al_get_bitmap_height(buffer)/2, result->sprite[i].w/2, result->sprite[i].h/2, SHIP_RATIO, SHIP_RATIO, i*(PI/2.0), 0);
                result->anim.current_z=0;
                result->anim.current_float_dir = UP;
                result->anim.float_speed = SHIP_FLOAT_SPEED;
                result->anim.frame_counter = 0;
                result->current_dir = UP;
                result->is_moving = 0;
                result->speed = SHIP_SPEED;
                result->x=W/2-result->sprite[UP].w/2;
                result->y=H/2-result->sprite[UP].h/2;
            }
        }
        else
        {
            fprintf(stderr, "Error allocating memory for new ship sprites\n");
        }
    }
    else
    {
        fprintf(stderr, "Error creating spaceship\n");
    }
    return result;
}

void print_ship_on_screen(Ship* ship)
{
    if(ship != NULL)
    {
        al_draw_bitmap(ship->sprite[ship->current_dir].sprite, ship->x, ship->y + ship->anim.current_z, 0);
    }
}

void animate_ship(Ship *ship)
{
    double theta = 2.0*PI*(ship->anim.frame_counter*ship->anim.float_speed/FPS);
    double float_value = DELTA_Z_MAX * sin(theta);
    ship->anim.current_z = (int)float_value;
    ship->anim.frame_counter = (ship->anim.frame_counter + 1)%(int)(FPS/ship->anim.float_speed);
}

void move_ship(Ship *ship)
{
    if(ship->is_moving)
    {
        switch (ship->current_dir)
        {
            case UP:
                ship->y-=ship->speed;
                break;
            case DOWN:
                ship->y+=ship->speed;
                break;
            case LEFT:
                ship->x-=ship->speed;
                break;
            case RIGHT:
                ship->x+=ship->speed;
                break;
            default:
                break;
        }
    }
}
