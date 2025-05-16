#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "jeu.h"
#define LEN_CASE 111.1
#define TAILLE_PLATEAU 14
#define FRAME_WIDTH 111
#define FRAME_HEIGHT 111
#define FRAME_COUNT 4
#define FRAME_DELAY 10



void gravite(int* jump,float *y1,float *y2,float *x1,float *x2,Obstacle* tabObst,int *g) {
    if(*jump>0) {
        *jump-=1;
        *y1-=10;
        *y2-=10;
    }
    else if (*y1+5<=789 && *y2+5<=789) {
        for(int k=0;k<10;k++) {
            if ((*y2<tabObst[k].y1-15 ||*y1>tabObst[k].y2-15 || (*x1>tabObst[k].x2 || *x2<tabObst[k].x1))) {
            }
            else {
                *g=1;
            }
        }
        if (*g==0) {
            *y1+=5;
            *y2+=5;
        }
        *g=0;
    }
}


void save(int matrice[TAILLE_PLATEAU][13]) {
    FILE *fichier = fopen("../save.txt", "w");  // "w" pour écrire (écrase si existe déjà)

    if (fichier == NULL) {
        //printf("Erreur lors de l'ouverture du fichier.\n");
    }

    // Parcours de la matrice et écriture dans le fichier
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 13; j++) {
            fprintf(fichier, "%d ", matrice[i][j]);  // un espace entre les colonnes
        }
        fprintf(fichier, "\n");  // retour à la ligne après chaque ligne de la matrice
    }

    fclose(fichier);
    //printf("Matrice écrite avec succès dans 'save.txt'\n");

}
void place_obstacle(Obstacle* tabObst,ALLEGRO_BITMAP *image, int matrice[TAILLE_PLATEAU][13]) {
    ALLEGRO_COLOR blue=al_map_rgb(70,135,225);
    //al_draw_filled_rectangle(555,555,666,666,blue);
    for (int i=0;i<10;i++) {
        if(tabObst[i].life>0) {
            al_draw_scaled_bitmap(image,0,0,360, 360,tabObst[i].x1-20,tabObst[i].y1-2,150,150,0);
        }
        else {
            int a=tabObst[i].x1/100;
            int b=tabObst[i].y1/100;
            matrice[a][b]=0;
            save(matrice);
            tabObst[i].x1=0;
            tabObst[i].x2=0;
            tabObst[i].y1=0;
            tabObst[i].y2=0;
        }
    }


}
void plateau(Obstacle* tabObst,ALLEGRO_BITMAP *image, int matrice[TAILLE_PLATEAU][13]) {
    ALLEGRO_COLOR black=al_map_rgb(255,255,255);

    for (int i=0;i<9;i++) {
        for(int j=0;j<13;j++) {
            al_draw_rectangle(j*LEN_CASE,i*LEN_CASE,(j+1)*LEN_CASE,(i+1)*LEN_CASE,black,1);
        }
    }
    place_obstacle(tabObst,image,matrice);
}

void renderPlayer(float x1, float y1, float x2, float y2,ALLEGRO_BITMAP *spritesheet, int frame) {
    ALLEGRO_COLOR c=al_map_rgb(150,200,0);
    //al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap_region(
                spritesheet,
                frame * FRAME_WIDTH, 0,         // position dans la spritesheet
                FRAME_WIDTH, FRAME_HEIGHT,      // taille de la frame
                x1 - FRAME_WIDTH / 2,
                y1 - FRAME_HEIGHT / 2,
                0
            );
    //al_draw_filled_rectangle(x1,y1,x2,y2,c);
}

void renderFireball(int i, float x1, float y1, float x2, float y2) {
    ALLEGRO_COLOR c=al_map_rgb(200,50,50);
    //al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(x1,y1,x2,y2,c);
}
