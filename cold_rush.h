#include <allegro5/allegro.h>

#define WIDTH 1532
#define HEIGHT 789
#define playx 90
#define playy 60
#define WIDTH_TEXTE 1000
#define HEIGHT_TEXTE 250

#define GLACON5W 1200
#define GLACON5H 520
#define GLACON6W 920
#define GLACON6H 370
#define GLACON9W 200
#define GLACON9H 100


typedef struct {
    int x, y, w, h;
} Bouton;



bool clicDansBouton(int x, int y, Bouton bouton);
bool sBouton(int sx, int sy, Bouton bouton);
void dessinerTout(ALLEGRO_BITMAP* background);
void dessin_glacon(ALLEGRO_BITMAP* glacon,int current_bg,int glacon1,int glacon2,int glacon3);
void pinterrogation(ALLEGRO_BITMAP** background,ALLEGRO_EVENT_QUEUE* file,Bouton fermerQuestion,int* a,int current_bg);
void display_mute_status_in_menu(bool is_sound_muted, ALLEGRO_BITMAP *son_coupe, int ssonx, int ssony,int* son);
void dessin_son_coupe(ALLEGRO_BITMAP* son_coupe,int ssonx,int ssony);
void dessin_son(ALLEGRO_BITMAP* son_actif,int ssonx,int ssony);
void dessinPlay(ALLEGRO_BITMAP* play);
void dessinStop(ALLEGRO_BITMAP* stop);
void dessin_jauge(ALLEGRO_BITMAP* jauge);
void dessin_horloge(ALLEGRO_BITMAP* horloge);
void dessin_maison(ALLEGRO_BITMAP* home,Bouton maison);
void dessinHomeGros(ALLEGRO_BITMAP* home);
void dessin_question(ALLEGRO_BITMAP* quest,Bouton question);
void dessinInterroGros(ALLEGRO_BITMAP* interro);
void dessin_poireau(ALLEGRO_BITMAP* poireau);
void dessinfin(ALLEGRO_BITMAP* fin_reussi);
void dessintomate(ALLEGRO_BITMAP* tomate_fin);
void dessinjouer(ALLEGRO_BITMAP* jouer_fin);
void dessinJouer(ALLEGRO_BITMAP* jouer);
void dessinHome(ALLEGRO_BITMAP* home);
void dessinInterro(ALLEGRO_BITMAP* interro);

