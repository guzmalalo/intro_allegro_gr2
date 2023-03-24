#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#define LARGEUR 800
#define HAUTEUR 600
#define COULEUR_ALEA al_map_rgb(rand()%256, rand()%256, rand()%256)
#define RED al_map_rgb(255, 0, 0)

enum{
    GAUCHE,
    DROITE,
    HAUT,
    BAS,
};

typedef struct {
    int x, y, largeur, hauteur;
} Rect;

void centrerRectangle(Rect* r, int largeur, int hauteur) {
    r->largeur = largeur;
    r->hauteur = hauteur;
    r->x = LARGEUR / 2 - r->largeur / 2;
    r->y = HAUTEUR / 2 - r->hauteur / 2;
}

void dessiner(Rect r) {
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_filled_rectangle(r.x, r.y, r.x+r.largeur, r.y+r.hauteur, RED);
    al_flip_display();
}

int main() {
    // definitions
    bool fini = false;
    Rect rectangle= {0};
    ALLEGRO_EVENT_QUEUE* fifo = NULL;
    ALLEGRO_DISPLAY* fenetre = NULL;
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_EVENT event;
    bool TE[4] = {false};

    // initialisation
    srand(time(NULL));
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());

    // Creation
    // largeur, hauteur, x et y au centre
    centrerRectangle(&rectangle, 80, 60);

    // display
    fenetre = al_create_display(LARGEUR, HAUTEUR);
    assert(fenetre != NULL);
    al_set_window_title(fenetre, "ECE");
    // al_set_window_position(fenetre, 0, 0);

    // timer
    timer = al_create_timer(1.0/24.0);
    al_start_timer(timer);

    // file fifo
    fifo = al_create_event_queue();
    al_register_event_source(fifo, al_get_keyboard_event_source());
    al_register_event_source(fifo, al_get_display_event_source(fenetre));
    al_register_event_source(fifo, al_get_timer_event_source(timer));

    // premier affichage
    dessiner(rectangle);

    while(!fini) {
        al_wait_for_event(fifo, &event);
        //printf("On vient de piocher un event de type %d.\n", event.type);
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: { // 42
                fini = true;
                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN: { // 10
                if(event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                    TE[BAS] = true;
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_UP) {
                    TE[HAUT] = true;
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    TE[DROITE] = true;
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    TE[GAUCHE] = true;
                }
                break;
            }
            case ALLEGRO_KEY_UP:
                if(event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                    TE[BAS] = false;
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_UP) {
                    TE[HAUT] = false;
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    TE[DROITE] = false;
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    TE[GAUCHE] = false;
                }
                break;
            case ALLEGRO_EVENT_TIMER:
                if(TE[BAS]){
                    if((rectangle.y+rectangle.hauteur) < HAUTEUR){
                        rectangle.y += 10;
                    }
                }
                if(TE[HAUT]){

                        rectangle.y -= 10;

                }
                dessiner(rectangle);
                break;
            default: {
                printf("Cet event est ignore (%d).\n", event.type);
            }
        }

    }

    dessiner(rectangle);

    al_destroy_display(fenetre);

    return 0;
}