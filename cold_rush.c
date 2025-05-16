#include "cold_rush.h"
#include <allegro5/allegro.h>
#include <stdio.h>



void dessinerTout(ALLEGRO_BITMAP* background) {


        al_draw_scaled_bitmap(
                background,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(background),  // largeur originale
                al_get_bitmap_height(background), // hauteur originale
                0, 0,             // position sur l’écran
                WIDTH, HEIGHT,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );

    al_flip_display();
}

void dessin_son_coupe(ALLEGRO_BITMAP* son_coupe,int ssonx, int ssony) {
    al_draw_scaled_bitmap(
                son_coupe,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(son_coupe),  // largeur originale
                al_get_bitmap_height(son_coupe), // hauteur originale
                ssonx,ssony-4.5,             // position sur l’écran
                80, 53,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}

void dessin_son(ALLEGRO_BITMAP* son_actif,int ssonx, int ssony) {
    al_draw_scaled_bitmap(
                son_actif,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(son_actif),  // largeur originale
                al_get_bitmap_height(son_actif), // hauteur originale
                ssonx,ssony-4.5,             // position sur l’écran
                80, 53,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}

void dessinPlay(ALLEGRO_BITMAP* play) {
    al_draw_scaled_bitmap(
                play,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(play),  // largeur originale
                al_get_bitmap_height(play), // hauteur originale
                playx-12,playy-6,             // position sur l’écran
                80, 53,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}

void dessinStop(ALLEGRO_BITMAP* stop) {
    al_draw_scaled_bitmap(
                stop,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(stop),  // largeur originale
                al_get_bitmap_height(stop), // hauteur originale
                playx-12,playy-6,             // position sur l’écran
                80, 53,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}
void dessin_horloge(ALLEGRO_BITMAP* horloge) {
    al_draw_scaled_bitmap(
                horloge,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(horloge),  // largeur originale
                al_get_bitmap_height(horloge), // hauteur originale
                playx-12+100,playy-6,             // position sur l’écran
                80, 53,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}

void dessin_maison(ALLEGRO_BITMAP* home,Bouton maison) {
    al_draw_scaled_bitmap(
                home,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(home),  // largeur originale
                al_get_bitmap_height(home), // hauteur originale
                maison.x,maison.y-5,             // position sur l’écran
                80, 53,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}

void dessin_question(ALLEGRO_BITMAP* quest,Bouton question) {

    al_draw_scaled_bitmap(
                quest,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(quest),  // largeur originale
                al_get_bitmap_height(quest), // hauteur originale
                question.x-12,question.y-5,             // position sur l’écran
                80, 53,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}


bool clicDansBouton(int x, int y, Bouton bouton) {
    return (x >= bouton.x && x <= bouton.x + bouton.w && y >= bouton.y && y <= bouton.y + bouton.h);
}

bool sBouton(int sx, int sy, Bouton bouton) {
    return (sx>=bouton.x && sx<= bouton.x + bouton.w && sy >= bouton.y && sy<= bouton.y + bouton.h);
}




void pinterrogation(ALLEGRO_BITMAP** background,ALLEGRO_EVENT_QUEUE* file,Bouton fermerQuestion,int* a,int current_bg) {
    while(*a) {
        current_bg = 3;
        dessinerTout(background[current_bg]);
        ALLEGRO_EVENT event;
        al_wait_for_event(file, &event);
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int sx = event.mouse.x;
            int sy = event.mouse.y;

            if(clicDansBouton(sx,sy,fermerQuestion)) {
                *a = 0;
            }
        }
    }
}

void display_mute_status_in_menu(bool is_sound_muted, ALLEGRO_BITMAP *son_coupe, int ssonx, int ssony,int* son) {
    if (is_sound_muted && son_coupe != NULL) {
        *son = 1;
    }else {
        *son = 0;
    }
}

void dessin_poireau(ALLEGRO_BITMAP* poireau) {

    al_draw_scaled_bitmap(
                    poireau,                // image source
                    0, 0,                 // coordonnées dans l'image source
                    al_get_bitmap_width(poireau),  // largeur originale
                    al_get_bitmap_height(poireau), // hauteur originale
                    WIDTH_TEXTE,HEIGHT_TEXTE,             // position sur l’écran
                    450, 300,             // taille de destination
                    0                    // flags (0 pour aucun effet)
                );
}

void dessin_jauge(ALLEGRO_BITMAP* jauge) {

    al_draw_scaled_bitmap(
                   jauge,                // image source
                   0, 0,                 // coordonnées dans l'image source
                   al_get_bitmap_width(jauge),  // largeur originale
                   al_get_bitmap_height(jauge), // hauteur originale
                   280,57,             // position sur l’écran
                   130,50,             // taille de destination
                   0                    // flags (0 pour aucun effet)
               );
}


void dessin_glacon(ALLEGRO_BITMAP* glacon,int current_bg,int glacon1,int glacon2,int glacon3) {

    if (current_bg == 5 && glacon1 == 1) {
        al_draw_scaled_bitmap(
                   glacon,                // image source
                   0, 0,                 // coordonnées dans l'image source
                   al_get_bitmap_width(glacon),  // largeur originale
                   al_get_bitmap_height(glacon), // hauteur originale
                   GLACON5W,GLACON5H,             // position sur l’écran
                   130,130,             // taille de destination
                   0                    // flags (0 pour aucun effet)
               );
    }
    else if (current_bg == 6 && glacon2 == 1) {
    al_draw_scaled_bitmap(
                   glacon,                // image source
                   0, 0,                 // coordonnées dans l'image source
                   al_get_bitmap_width(glacon),  // largeur originale
                   al_get_bitmap_height(glacon), // hauteur originale
                   GLACON6W,GLACON6H,             // position sur l’écran
                   130,130,             // taille de destination
                   0                    // flags (0 pour aucun effet)
               );
    }
    else if (current_bg == 9 && glacon3 == 1) {
        al_draw_scaled_bitmap(
                   glacon,                // image source
                   0, 0,                 // coordonnées dans l'image source
                   al_get_bitmap_width(glacon),  // largeur originale
                   al_get_bitmap_height(glacon), // hauteur originale
                   GLACON9W,GLACON9H,             // position sur l’écran
                   130,130,             // taille de destination
                   0                    // flags (0 pour aucun effet)
               );
    }
}

void dessinfin(ALLEGRO_BITMAP* fin_reussi) {
    al_draw_scaled_bitmap(
                   fin_reussi,                // image source
                   0, 0,                 // coordonnées dans l'image source
                   al_get_bitmap_width(fin_reussi),  // largeur originale
                   al_get_bitmap_height(fin_reussi), // hauteur originale
                   500,200,             // position sur l’écran
                   600,400,             // taille de destination
                   0                    // flags (0 pour aucun effet)
               );
}

void dessintomate(ALLEGRO_BITMAP* tomate_fin) {

        al_draw_scaled_bitmap(
                       tomate_fin,                // image source
                       0, 0,                 // coordonnées dans l'image source
                       al_get_bitmap_width(tomate_fin),  // largeur originale
                       al_get_bitmap_height(tomate_fin), // hauteur originale
                       700,600,             // position sur l’écran
                       200,200,             // taille de destination
                       0                    // flags (0 pour aucun effet)
                   );

    }

void dessinjouer(ALLEGRO_BITMAP* jouer_fin) {

    al_draw_scaled_bitmap(
                           jouer_fin,                // image source
                           0, 0,                 // coordonnées dans l'image source
                           al_get_bitmap_width(jouer_fin),  // largeur originale
                           al_get_bitmap_height(jouer_fin), // hauteur originale
                           720,90,             // position sur l’écran
                           200,50,             // taille de destination
                           0                    // flags (0 pour aucun effet)
                       );

}

void dessinHomeGros(ALLEGRO_BITMAP* home) {
    al_draw_scaled_bitmap(
                home,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(home),  // largeur originale
                al_get_bitmap_height(home), // hauteur originale
                1284,50,             // position sur l’écran
                90, 63,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}

void dessinInterroGros(ALLEGRO_BITMAP* interro) {
    al_draw_scaled_bitmap(
                interro,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(interro),  // largeur originale
                al_get_bitmap_height(interro), // hauteur originale
                1378,50,             // position sur l’écran
                90, 63,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}

void dessinJouer(ALLEGRO_BITMAP* jouer) {
    al_draw_scaled_bitmap(
                jouer,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(jouer),  // largeur originale
                al_get_bitmap_height(jouer), // hauteur originale
                650,515,             // position sur l’écran
                230, 68,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}

void dessinHome(ALLEGRO_BITMAP* home) {
    al_draw_scaled_bitmap(
                home,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(home),  // largeur originale
                al_get_bitmap_height(home), // hauteur originale
                1287,54,             // position sur l’écran
                80, 53,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}

void dessinInterro(ALLEGRO_BITMAP* interro) {
    al_draw_scaled_bitmap(
                interro,                // image source
                0, 0,                 // coordonnées dans l'image source
                al_get_bitmap_width(interro),  // largeur originale
                al_get_bitmap_height(interro), // hauteur originale
                1381,54,             // position sur l’écran
                80, 53,             // taille de destination
                0                    // flags (0 pour aucun effet)
            );
}




