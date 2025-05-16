#ifndef JEU_H
#define JEU_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#define LEN_CASE 111.1
#define TAILLE_PLATEAU 14
#define FRAME_WIDTH 111
#define FRAME_HEIGHT 111
#define FRAME_COUNT 4
#define FRAME_DELAY 10

typedef struct {
    float x1,y1,x2,y2;
    bool isActive;
    char direction;
} Fireball;

typedef struct {
    float x1,y1,x2,y2;
    int life;
}Obstacle;

typedef struct {
    float x1,y1,x2,y2;
    int life;
    char direction;
}joueur;


void gravite(int* jump,float *y1,float *y2,float *x1,float *x2,Obstacle* tabObst,int *g);
void save(int matrice[TAILLE_PLATEAU][13]);
void place_obstacle(Obstacle* tabObst,ALLEGRO_BITMAP *image, int matrice[TAILLE_PLATEAU][13]);
void plateau(Obstacle* tabObst,ALLEGRO_BITMAP *image, int matrice[TAILLE_PLATEAU][13]);
void renderPlayer(float x1, float y1, float x2, float y2,ALLEGRO_BITMAP *spritesheet, int frame);
void renderFireball(int i, float x1, float y1, float x2, float y2);
#endif
