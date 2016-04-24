#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "screen.h"
#include "ship.h"

#define BACKGROUND_FILE     "../data/space_background/blue_space.jpg"

int main (int argc, char *argv[])
{
    Ship* ship = NULL;
    ALLEGRO_TIMER *main_timer = NULL;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_COLOR cyan = al_map_rgb(0,255,255);
    ALLEGRO_BITMAP *space_background = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    bool redraw = true;
    ALLEGRO_EVENT ev;

    if(!al_init())
    {
        fprintf(stderr, "Error initializing Allegro");
        exit(EXIT_FAILURE);
    }
    if(!al_init_image_addon())
    {
        fprintf(stderr, "Error initializing Allegro");
        exit(EXIT_FAILURE);
    }
    if(!al_install_keyboard())
    {
        fprintf(stderr, "Error initializing keyboard\n");
        exit(EXIT_FAILURE);
    }
    display=al_create_display(W, H);

    if(display == NULL)
    {
        fprintf(stderr, "Error creating main display");
        exit(EXIT_FAILURE);
    }

    space_background = al_load_bitmap(BACKGROUND_FILE);
    if(space_background == NULL)
    {
        fprintf(stderr, "Error loading background\n");
        exit(EXIT_FAILURE);
    }
    ship=create_new_ship("../data/spaceship.png");
    ship->current_dir = DOWN;
    al_set_target_backbuffer(display);
    al_draw_bitmap(space_background, 0, 0, 0);
    print_ship_on_screen(ship);
    al_flip_display();

    main_timer=al_create_timer(1.0/FPS);
    if(main_timer == NULL)
    {
        fprintf(stderr, "Error creating main timer\n");
        exit(EXIT_FAILURE);
    }

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(main_timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(main_timer);

    while(1)
    {
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else
        {
            switch (ev.type)
            {
                case ALLEGRO_EVENT_TIMER:
                    redraw = true;
                    break;
                case ALLEGRO_EVENT_KEY_DOWN:
                    switch(ev.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_UP:
                            ship->is_moving = 1;
                            ship->current_dir = UP;
                            break;
                        case ALLEGRO_KEY_DOWN:
                            ship->is_moving = 1;
                            ship->current_dir = DOWN;
                            break;
                        case ALLEGRO_KEY_LEFT:
                            ship->is_moving = 1;
                            ship->current_dir = LEFT;
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            ship->is_moving = 1;
                            ship->current_dir = RIGHT;
                            break;
                        default:
                            break;
                    }
                    break;
                case ALLEGRO_EVENT_KEY_UP:
                    ship->is_moving = 0;
                    break;
                default:
                    break;
            }
        }

        if(redraw && al_event_queue_is_empty(event_queue))
        {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap(space_background, 0, 0, 0);
            move_ship(ship);
            animate_ship(ship);
            print_ship_on_screen(ship);
            al_flip_display();
        }
    }
    al_destroy_timer(main_timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

	return 0;
}

