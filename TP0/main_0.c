#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>

#define LARGEUR 800
#define HAUTEUR 600
#define COLOR_AL al_map_rgb(rand()%255,rand()%255,rand()%255 )

int main()
{
 // Definitions
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * fifo = NULL;
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_EVENT event= {0};
    int fini = 0;

    // Initialisation
    assert(al_init());
    assert(al_install_keyboard());
    assert(al_install_mouse());

    // Creation
    // display
    display = al_create_display(LARGEUR, HAUTEUR);

    // timer
    timer = al_create_timer(1.0/2.0);
    al_start_timer(timer);

    // file
    fifo = al_create_event_queue();
    al_register_event_source(fifo, al_get_display_event_source(display));
    al_register_event_source(fifo, al_get_keyboard_event_source());
    al_register_event_source(fifo, al_get_mouse_event_source());
    al_register_event_source(fifo, al_get_timer_event_source(timer));


    // Premier affichage
    al_clear_to_color(al_map_rgb(255,255,255));
    al_flip_display();

    while(!fini){

        al_wait_for_event(fifo, &event);

        switch (event.type) {

            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        fini = 1;
                        break;
                    default:
                        printf("La touche est %s \n", al_keycode_to_name(event.keyboard.keycode));
                }
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                printf("x:%d , y:%d  \n", event.mouse.x, event.mouse.y);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                al_clear_to_color(COLOR_AL);
                al_flip_display();
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini =1;
                break;
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(COLOR_AL);
                al_flip_display();
                break;
            default:
                printf("Le event numero %d, n'est pas géré \n", event.type);
                break;
        }

    }

    // Free
    al_destroy_display(display);
    al_destroy_event_queue(fifo);


    return 0;
}