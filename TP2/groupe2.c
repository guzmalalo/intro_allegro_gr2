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
    al_draw_filled_rectangle(r.x, r.y, r.x+r.largeur, r.y+r.hauteur, COULEUR_ALEA);
    al_flip_display();
}

int main() {
    bool fini = false;
    Rect rectangle;
    ALLEGRO_EVENT_QUEUE* fifo = NULL;
    ALLEGRO_DISPLAY* fenetre = NULL;
    ALLEGRO_EVENT event;

    srand(time(NULL));
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());

    centrerRectangle(&rectangle, 80, 60);

    fenetre = al_create_display(LARGEUR, HAUTEUR);
    assert(fenetre != NULL);
    al_set_window_title(fenetre, "ECE");
    // al_set_window_position(fenetre, 0, 0);

    fifo = al_create_event_queue();

    al_register_event_source(fifo, al_get_keyboard_event_source());
    al_register_event_source(fifo, al_get_display_event_source(fenetre));

    while(!fini) {
        al_wait_for_event(fifo, &event);
        printf("On vient de piocher un event de type %d.\n", event.type);
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: { // 42
                fini = true;
                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN: { // 10
                if(event.keyboard.keycode == ALLEGRO_KEY_T) {

                }
                break;
            }
            default: {
                printf("Cet event est ignore (%d).\n", event.type);
            }
        }

    }

    dessiner(rectangle);

    al_destroy_display(fenetre);

    return 0;
}