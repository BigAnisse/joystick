#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/joystick.h>
#include <stdbool.h>
#include "cold_rush.h"
#include "son1.h"
#include "jeu.h"

#define WIDTH 1532
#define HEIGHT 789
#define GLACON 4
#define NB_BACKGROUNDS 13
#define NB_NIVEAUX_GLACONS 3
#define NB_IMAGES_JAUGE 4


int main(void) {


    // Utilisez
    if (!al_init()) {
        fprintf(stderr, "Erreur: échec de l'initialisation d'Allegro\n");
        return -1;
    }
    assert(al_install_mouse());
    assert(al_install_keyboard());
    assert(al_init_image_addon());
    assert(al_install_joystick());
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    if (!al_install_audio()) {
        fprintf(stderr, "Erreur: impossible d'initialiser le système audio\n");
        return -1;
    }
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "Erreur: impossible d'initialiser les codecs audio\n");
        return -1;
    }
    if (!al_reserve_samples(1)) {
        fprintf(stderr, "Erreur: impossible de réserver des samples audio\n");
        return -1;
    }

    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    ALLEGRO_DISPLAY* fenetre = NULL;
    ALLEGRO_EVENT_QUEUE* file = al_create_event_queue();
    ALLEGRO_EVENT* event = malloc(sizeof(ALLEGRO_EVENT));
    ALLEGRO_TIMER* timer_dessin = NULL;
    ALLEGRO_TIMER* timer_pause = NULL;


    ALLEGRO_BITMAP* son_coupe = NULL;
    ALLEGRO_BITMAP* son_actif = NULL;
    ALLEGRO_BITMAP* play = NULL;
    ALLEGRO_BITMAP* stop = NULL;
    ALLEGRO_BITMAP* poireau = NULL;
    ALLEGRO_BITMAP *tomD = NULL;
    ALLEGRO_BITMAP *tomG = NULL;
    ALLEGRO_BITMAP* glacon_avant = NULL;
    ALLEGRO_BITMAP* horloge = NULL;
    ALLEGRO_BITMAP* horloge1 = NULL;
    ALLEGRO_BITMAP* horloge2 = NULL;
    ALLEGRO_BITMAP* horloge3 = NULL;
    ALLEGRO_BITMAP* horloge4 = NULL;
    ALLEGRO_BITMAP* jauge = NULL;
    ALLEGRO_BITMAP* jauge1 = NULL;
    ALLEGRO_BITMAP* jauge2 = NULL;
    ALLEGRO_BITMAP* jauge3 = NULL;
    ALLEGRO_BITMAP* jauge4 = NULL;
    ALLEGRO_BITMAP* tomate_fin = NULL;
    ALLEGRO_BITMAP* jouer_fin = NULL;
    ALLEGRO_BITMAP* homeclaire = NULL;
    ALLEGRO_BITMAP* interroclaire = NULL;
    ALLEGRO_BITMAP* Jouer = NULL;


    ALLEGRO_BITMAP* home = NULL;
    ALLEGRO_BITMAP* quest = NULL;
    ALLEGRO_BITMAP* fin_reussi = NULL;



    ALLEGRO_FONT *font = NULL;
    ALLEGRO_SAMPLE* music = NULL;
    ALLEGRO_SAMPLE_INSTANCE* music_instance = NULL;
    ALLEGRO_MIXER *mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    ALLEGRO_VOICE *voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);



    bool running = true;
    bool fini = false;
    bool is_sound_muted = false;
    bool show_text = false;
    bool afficher_homeclaire = false;
    bool afficher_homeclaireGros = false;
    bool afficher_interroclaire = false;
    bool afficher_interroclaireGros = false;
    bool afficherJouer = false;
    bool  pauseActive = false;

    ALLEGRO_BITMAP* backgrounds[NB_BACKGROUNDS];
    backgrounds[0] = al_load_bitmap("../images/PLTO-INTERFACE-01.png");
    backgrounds[1] = al_load_bitmap("../images/PLTO-INTERFACE-02.png");
    backgrounds[2] = al_load_bitmap("../images/PLTO-INTERFACE-06.png");
    backgrounds[3] = al_load_bitmap("../images/PLTO-INTERFACE-03.png");
    backgrounds[4] = al_load_bitmap("../images/PLTO_1.png"); // niveau 1
    backgrounds[5] = al_load_bitmap("../images/PLTO_2.png"); // niveau 2
    backgrounds[6] = al_load_bitmap("../images/PLTO_3.png"); // niveau 3
    backgrounds[7] = al_load_bitmap("../images/PLTO_4.png"); // niveau 4
    backgrounds[8] = al_load_bitmap("../images/PLTO_5.png"); // niveau 5
    backgrounds[9] = al_load_bitmap("../images/PLTO_6.png"); // niveau 6
    backgrounds[10] = al_load_bitmap("../images/PLTO_7.png"); // niveau 7
    backgrounds[11] = al_load_bitmap("../images/PLTO-INTERFACE-05.png"); // fin gagne
    backgrounds[12] = al_load_bitmap("../images/PLTO-INTERFACE-04.png"); // fin perdu


    int current_bg = 0;
    int sx;
    int sy;
    int h = HEIGHT;
    int w = WIDTH;
    int a = 1;
    int p = 1;
    int dessin = 1;
    int son = 0;
    float x1=450,y1=450,x2=550,y2=550,z=0,q=0,s=0,d=0;
    Fireball* tabF = calloc(10,sizeof(Fireball));
    Obstacle* tabObst = calloc(10,sizeof(Obstacle));
    int obstZ=0;
    int obstS=0;
    int obstQ=0;
    int obstD=0;
    int jump=0;
    int g=0;
    float temps_ecoule = 0.0f;
    int temps = 0;
    int glace = 1;
    int glacon1 = 1;
    int glacon2 = 1;
    int glacon3 = 1;
    int victoire = 0;



    Bouton bouton = {w * 0.43, h * 0.67, 200, 40};
    Bouton maison = {w * 0.84, h * 0.076, 60, 40};
    Bouton question = {0.91 * w,0.076 * h, 60, 40};
    Bouton fermerQuestion = {0.34 * w,0.25 * h, 50, 35};
    Bouton volume = {0.78*w,0.076*h,60,40};
    Bouton niveau1 = {0.35*w,0.285*h,400,175};
    Bouton pause = {0.058*w,0.076*h,60,40};
    Bouton jouer = {0.47*w,0.114*h,200,50};
    int ssonx = volume.x;
    int ssony = volume.y;


    fenetre = al_create_display(WIDTH,HEIGHT);
    timer_dessin = al_create_timer(1.0/30.0);
    timer_pause = al_create_timer(300.0);

    al_register_event_source(file,al_get_keyboard_event_source());
    al_register_event_source(file,al_get_display_event_source(fenetre));
    al_register_event_source(file,al_get_joystick_event_source());
    al_register_event_source(file,al_get_mouse_event_source());
    al_register_event_source(file,timer_dessin);
    al_register_event_source(file,timer_pause);

    al_start_timer(timer_dessin);
    al_attach_mixer_to_voice(mixer, voice);



    joueur j1;
    j1.direction='E';

     al_install_mouse();

    ALLEGRO_JOYSTICK_STATE state;
    int num_joysticks = al_get_num_joysticks();
    if( num_joysticks == 1) {
        current_bg = 1;

    }else {
        current_bg = 0;

    }
    printf("Nombre de manettes détectées: %d\n", num_joysticks);
    if (num_joysticks > 0) {  // Ajouter cette vérification pour éviter les erreurs
        ALLEGRO_JOYSTICK *joystick = al_get_joystick(0);
        printf("Manette détectée: %s\n", al_get_joystick_name(joystick));
        printf("Nombre d'axes: %d\n", al_get_joystick_num_axes(joystick, 0));
        printf("Nombre de boutons: %d\n", al_get_joystick_num_buttons(joystick));

    }

    font = al_load_ttf_font("../fonts/ComicRelief-Regular.ttf",24,0);

    son_coupe = al_load_bitmap("../images/BOUTON-SON-2.png");
    son_actif = al_load_bitmap("../images/BOUTON-SON-1.png");
    play = al_load_bitmap("../images/BOUTON-PLAY-1.png");
    stop = al_load_bitmap("../images/BOUTON-STOP-1.png");
    poireau = al_load_bitmap("../images/BOUTON-TEXTE-POIREAU.png");
    tomD = al_load_bitmap("../images/Tomate/PERS-PROFIL-D/TOMATE_Profil_D_00000.png");
    tomG = al_load_bitmap("../images/Tomate/PERS-PROFIL-G/TOMATE_Profil_00000.png");
    glacon_avant = al_load_bitmap("../images/glacon.png");
    horloge1 = al_load_bitmap("../images/BOUTON-HORLOGE-1.png");
    horloge2 = al_load_bitmap("../images/BOUTON-HORLOGE-2.png");
    horloge3 = al_load_bitmap("../images/BOUTON-HORLOGE-3.png");
    horloge4 = al_load_bitmap("../images/BOUTON-HORLOGE-4.png");
    home = al_load_bitmap("../images/BOUTON-HOMEPAGE-1.png");
    quest = al_load_bitmap("../images/BOUTON-INFORMATIONS-1.png");
    fin_reussi = al_load_bitmap("../images/BOUTON-JEU-REUSSI.png");
    jauge1 = al_load_bitmap("../images/BOUTON-JAUGE-1.png");
    jauge2 = al_load_bitmap("../images/BOUTON-JAUGE-2.png");
    jauge3 = al_load_bitmap("../images/BOUTON-JAUGE-3.png");
    jauge4 = al_load_bitmap("../images/BOUTON-JAUGE-4.png");
    tomate_fin = al_load_bitmap("../images/TOMATE_00005.png");
    jouer_fin = al_load_bitmap("../images/BOUTON-JOUER-2.png");
    homeclaire = al_load_bitmap("../images/BOUTON-HOMEPAGE-2.png");
    interroclaire =  al_load_bitmap("../images/BOUTON-INFORMATIONS-2.png");
    Jouer = al_load_bitmap("../images/BOUTON-JOUER-1.png");






    for (int i = 0; i <= 12; i++) {
        if (!backgrounds[i]) {
            fprintf(stderr, "Erreur : image backgrounds[%d] introuvable !\n", i);
            exit(EXIT_FAILURE);
        }
    }


    music = al_load_sample("../music/MUSIQUE-COLD-RUSH.ogg");
    if (!music) {
        fprintf(stderr, "Erreur: impossible de charger le fichier audio ../music/MUSIQUE-COLD-RUSH.ogg\n");
        return -1;
    }
    music_instance = al_create_sample_instance(music);
    if (!music_instance) {
        fprintf(stderr, "Erreur: impossible de créer l'instance de sample\n");
        return -1;
    }
    al_set_sample_instance_playmode(music_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(music_instance, mixer);
    al_set_sample_instance_gain(music_instance, 0.5f);
    al_play_sample_instance(music_instance);
    if (!mixer) {
        fprintf(stderr, "Erreur: impossible de créer le mixer\n");
        return -1;
    }
    if (!voice) {
        fprintf(stderr, "Erreur: impossible de créer la voice\n");
        return -1;
    }

while(!fini) {

    al_wait_for_event(file, event);

    switch (event->type) {
        case ALLEGRO_EVENT_TIMER: {
            if (event->timer.source == timer_dessin) {


                if (temps==1) temps_ecoule += 1.0f/30.0f;
                if (temps_ecoule<75.0f) horloge = horloge1;
                else if(temps_ecoule<150.0f) horloge = horloge2;
                else if (temps_ecoule<225.0f) horloge = horloge3;
                else horloge = horloge4;
                if (glace == 1) jauge = jauge1;
                else if (glace == 2) jauge = jauge2;
                else if (glace == 3) jauge = jauge3;
                else if (glace == 4) jauge = jauge4;
                if (current_bg == 5 && (y2-600>=-10 && y2-600<=10 && x1>=1150 && x1<=1285) && glacon1 == 1) {
                    glacon1 = 0;
                    glace +=1;
                    victoire +=1;
                }
                if (current_bg == 6 && (y2-430<=10 && y2-430>=-10 && (x2>=950 && x2<=1100)) && glacon2 == 1) {
                    glacon2 = 0;
                    glace +=1;
                    victoire +=1;
                }
                if (current_bg == 9 &&(y2-180<=10 && y2-180>=-10 && (x2>=250 && x2<=390)) && glacon3 == 1) {
                    glacon3 = 0;
                    glace+=1;
                    victoire +=1;
                }
                al_clear_to_color(al_map_rgb(255,255,255));
                display_mute_status_in_menu(is_sound_muted,son_coupe, ssonx, ssony,&son);
                if (son == 1) {
                    dessinerTout(backgrounds[current_bg]);
                    if(current_bg != 11) {
                        dessin_son_coupe(son_coupe,ssonx,ssony);
                    }
                }else {
                    dessinerTout(backgrounds[current_bg]);
                    if(current_bg != 11) {
                        dessin_son(son_actif,ssonx,ssony);
                    }
                }
                if(afficher_homeclaire) {
                    dessinHome(homeclaire);
                }
                if(afficher_interroclaire) {
                    dessinInterro(interroclaire);
                }
                if(afficher_homeclaireGros) {
                    dessinHomeGros(homeclaire);
                }
                if(afficherJouer) {
                    dessinJouer(Jouer);
                }
                if(afficher_interroclaireGros) {
                    dessinInterroGros(interroclaire);
                }
                if (y1<=10 && current_bg == 4) {
                    current_bg = 5;
                    x1=100,y1=450,x2=200,y2=550;
                }
                if(y1>=700 && current_bg == 5) {
                    current_bg = 4;
                    x1=100,y1=200,x2=200,y2=300;
                }
                if (x1>=1400 && current_bg == 5) {
                    current_bg = 6;
                    x1=100,y1=400,x2=200,y2=500;
                }
                if (x1<10 && current_bg == 6) {
                    current_bg = 5;
                    x1=1300,y1=400,x2=1400,y2=500;
                }
                if (y1>=600 && current_bg == 6) {
                    current_bg = 7;
                    x1=300,y1=250,x2=400,y2=350;
                }
                if (y2<=50 && current_bg == 6) {
                    current_bg = 9;
                    x1=1200,y1=150,x2=1300,y2=250;
                }
                if (y1<=100 && current_bg == 7) {
                    current_bg = 6;
                    x1=100,y1=400,x2=200,y2=500;
                }
                if (y1<=100 && current_bg == 5) {
                    current_bg = 8;
                    x1=100,y1=450,x2=200,y2=550;
                }
                if (x1>=1400 && current_bg == 8) {
                    current_bg = 9;
                    x1=200,y1=100,x2=200,y2=200;
                }
                if (y1<=100 && current_bg == 8) {
                    current_bg = 10;
                    x1=100,y1=450,x2=200,y2=550;
                }
                if (y1>=650 && current_bg == 8) {
                    current_bg = 5;
                    x1=100,y1=200,x2=200,y2=300;
                }
                if(x1<=20 && current_bg == 9) {
                    current_bg = 8;
                    x1=1200,y1=200,x2=1300,y2=300;
                }
                if (y1>=650 && current_bg == 9) {
                    current_bg = 6;
                    x1=1200,y1=300,x2=1300,y2=400;
                }
                if (y1>=650 && current_bg == 10) {
                    current_bg = 8;
                    x1=100,y1=200,x2=200,y2=300;
                }
                if (current_bg == 11) {
                    dessinfin(fin_reussi);
                    dessintomate(tomate_fin);
                    dessinjouer(jouer_fin);
                    glacon1 = 1;
                    glacon2 = 1;
                    glacon3 = 1;
                    victoire = 0;
                }
                if (current_bg == 5 || current_bg == 6 || current_bg == 9) dessin_glacon(glacon_avant,current_bg,glacon1,glacon2,glacon3);
                if (dessin == 1 && current_bg != 11) {
                    dessinPlay(play);
                    al_stop_timer(timer_pause);
                    p=0;
                }
                if (dessin == 0 && current_bg != 11){
                    dessinStop(stop);
                    al_start_timer(timer_pause);
                    p=1;
                }
                for (int i=0;i<10;i++) {
                    renderFireball(i, tabF[i].x1, tabF[i].y1, tabF[i].x2, tabF[i].y2);
                }
                if (glace == 1 && current_bg == 10 && victoire == 3) {
                    current_bg = 11;
                }
                if (current_bg >= 4 && current_bg != 11) {
                    renderPlayer(x1,y1,x2,y2,tomD,tomG,j1);
                    dessin_horloge(horloge);
                    dessin_jauge(jauge);
                }
                if (current_bg != 11) {
                    dessin_maison(home,maison);
                    dessin_question(quest,question);
                }
                if(x1>=700 && x1<=1200 && current_bg == 4) {
                    al_draw_text(font, al_map_rgb(255, 255, 255), // Police et couleur (blanc)
                    1200, 500, // Position du texte (au-dessus du joueur)
                    ALLEGRO_ALIGN_CENTER, // Alignement du texte centré
                    "APPUIE SUR T"); // Le texte à afficher
                }
                if(x1>=1100 && current_bg == 10) {
                    al_draw_text(font, al_map_rgb(255, 255, 255), // Police et couleur (blanc)
                    1100, 150, // Position du texte (au-dessus du joueur)
                    ALLEGRO_ALIGN_CENTER, // Alignement du texte centré
                    "APPUIE SUR ENTREE"); // Le texte à afficher
                }
                if(show_text && current_bg == 4) {
                    dessin_poireau(poireau);
                }
                if (z==1) {
                    for(int k=0;k<10;k++){
                        if ((y1>tabObst[k].y2+15 || y2<tabObst[k].y1+15 || (x1>tabObst[k].x2 || x2<tabObst[k].x1))) {
                        }
                        else {
                            obstZ=1;
                        }
                    }
                    if (obstZ==0) {
                        y1-=15;
                        y2-=15;
                    }
                    obstZ=0;
                }

                if (s==1) {
                    for(int k=0;k<10;k++) {
                        if ((y2<tabObst[k].y1-15 ||y1>tabObst[k].y2-15 || (x1>tabObst[k].x2 || x2<tabObst[k].x1))) {
                        }
                        else {
                            obstS=1;
                        }
                    }
                    if (obstS==0) {
                        y1+=15;
                        y2+=15;
                    }
                    obstS=0;
                }
                if (q==1) {
                    if ((y2-x2+500<=100) && (y2-x2+400>=-100) && current_bg == 4) {
                        y2-=15;
                        x2-=15;
                        x1-=15;
                        y1-=15;
                        j1.direction='W';
                    }
                    else{
                        j1.direction='W';
                        for(int k=0;k<10;k++) {
                            if ((y2<tabObst[k].y1 || y1>tabObst[k].y2 || (x1>tabObst[k].x2+15 || x2<tabObst[k].x1+15))) {
                            }
                            else {
                                obstQ=1;
                            }
                        }
                        if (obstQ==0) {
                            x1-=15;
                            x2-=15;
                        }
                        obstQ=0;
                    }
                }

                if (d==1) {

                    j1.direction='E';
                    for(int k=0;k<10;k++) {
                        if ((y2<tabObst[k].y1 || y1>tabObst[k].y2 || (x1>tabObst[k].x2-5 || x2<tabObst[k].x1-15))) {
                        }
                        else {
                            obstD=1;
                        }
                    }
                    if (obstD==0) {
                        x1+=15;
                        x2+=15;
                    }
                    obstD=0;

                }
                gravite(&jump,&y1,&y2,&x1,&x2,tabObst,&g,current_bg);
                for (int i=0; i<10; i++) {
                    if (tabF[i].isActive) {
                        if (tabF[i].direction=='N'){
                            tabF[i].y1 -= 15;
                            tabF[i].y2 -= 15;
                        }
                        else if (tabF[i].direction=='S'){
                            tabF[i].y1 += 15;
                            tabF[i].y2 += 15;
                        }
                        else if (tabF[i].direction=='E'){
                            tabF[i].x1 += 15;
                            tabF[i].x2 += 15;
                        }
                        else if (tabF[i].direction=='W'){
                            tabF[i].x1 -= 15;
                            tabF[i].x2 -= 15;
                        }

                        float xf1 = tabF[i].x1;
                        float xf2 = tabF[i].x2;
                        float yf1 = tabF[i].y1;
                        float yf2 = tabF[i].y2;
                        if (tabF[i].y1 < -100 || tabF[i].y2>1532 || tabF[i].x1 < -100 ||tabF[i].x2 > 1532) {
                            tabF[i].isActive = false;
                        }
                        for (int j=0;j<10;j++) {
                            if(tabObst[j].y2!=0) {
                                if(tabF[i].y1 < tabObst[j].y2 && tabF[i].y2>tabObst[j].y1 && (tabF[i].x1<tabObst[j].x2 && tabF[i].x2>tabObst[j].x1)) {
                                    tabF[i].isActive = false;
                                    tabObst[j].life-=1;
                                }
                            }
                        }
                    }
                    else {
                        tabF[i].y1 = 0;
                        tabF[i].y2 = 0;
                    }
                }
                al_flip_display();
            }
            else if (event->timer.source == timer_pause) {

                current_bg = 11;
                dessinerTout(backgrounds[current_bg]);
                al_flip_display();
                al_rest(10.0);
                for(int i=0;i < NB_BACKGROUNDS; i++) al_destroy_bitmap(backgrounds[i]);
                al_destroy_bitmap(son_coupe);
                al_destroy_bitmap(son_actif);
                al_destroy_bitmap(play);
                al_destroy_bitmap(stop);
                al_destroy_bitmap(poireau);
                al_destroy_bitmap(tomD);
                al_destroy_bitmap(tomG);
                al_destroy_bitmap(glacon_avant);
                al_destroy_bitmap(horloge1);
                al_destroy_bitmap(horloge2);
                al_destroy_bitmap(horloge3);
                al_destroy_bitmap(horloge4);
                al_destroy_bitmap(home);
                al_destroy_bitmap(quest);
                al_destroy_bitmap(fin_reussi);
                al_destroy_bitmap(jauge1);
                al_destroy_bitmap(jauge2);
                al_destroy_bitmap(jauge3);
                al_destroy_bitmap(jauge4);
                al_destroy_bitmap(tomate_fin);
                al_destroy_bitmap(jouer_fin);
                al_destroy_font(font);
                al_destroy_display(fenetre);
                al_destroy_event_queue(file);
                al_destroy_timer(timer_dessin);
                al_destroy_timer(timer_pause);
                al_destroy_sample_instance(music_instance);
                al_destroy_mixer(mixer);
                al_destroy_voice(voice);
                al_destroy_sample(music);
                al_destroy_font(font);
                al_uninstall_audio();
                free(event);
                free(tabF);
                free(tabObst);
                return 0;
            }
            break;
        }

        case ALLEGRO_EVENT_MOUSE_AXES: {

            sx = event->mouse.x;
            sy = event->mouse.y;

            if ((current_bg == 0 || current_bg == 1) && sBouton(sx, sy, bouton)) {
                current_bg = 1;
            }
            if (current_bg == 1 && sBouton(sx,sy,bouton)==false) {
                current_bg = 0;
            }
            break;
        }
        case ALLEGRO_EVENT_JOYSTICK_AXIS: {

            int stick = event->joystick.stick;
            int axis = event->joystick.axis;
            float pos = event->joystick.pos;
            float deadzone = 0.7f;

            static bool joystickActivePrecD = false;

            if (stick == 0 && axis == 0) {
                bool joystickActiveNowD = (pos > deadzone);
                if (joystickActiveNowD && !joystickActivePrecD) {
                    // Le joystick vient juste d'être incliné vers la droite

                    if (current_bg == 1) {
                        afficher_homeclaire = true;
                        current_bg = 0;
                    }
                    else if (current_bg == 0 && afficher_homeclaire) {
                        afficher_homeclaire = false;
                        afficher_interroclaire = true;
                        current_bg = 0;
                    }
                }

                joystickActivePrecD = joystickActiveNowD;
            }

            static bool joystickActivePrecG = false;
            if(stick == 0 && axis == 0) {
                bool joystickActiveNowG = (pos < -deadzone);
                if (joystickActiveNowG && !joystickActivePrecG) {

                    if (current_bg == 0 && afficher_interroclaire == true) {
                        afficher_interroclaire = false;
                        afficher_homeclaire  = true;

                    }else if (current_bg == 0 && afficher_homeclaire) {
                        afficher_homeclaire = false;

                        current_bg = 1;
                    }else if (current_bg == 1 ) {


                        current_bg = 1;
                    }
                }

                joystickActivePrecG = joystickActiveNowG;
            }

            if(stick == 0 && axis == 1 && pos > deadzone) {
                z = 1;
            } else {
                z = 0;
            }

            if(stick == 0 && axis == 1 && pos < -deadzone) {
                s = 1;
            } else {
                s = 0;
            }
            if(stick == 0 && axis == 0 && pos > deadzone) {
                d = 1;
            } else {
                d = 0;
            }
            if(stick == 0 && axis == 0 && pos < -deadzone) {
                q = 1;
            } else {
                q = 0;
            }



           if(pauseActive) {
               if(stick == 0 && axis == 0 && pos > deadzone && current_bg == 2) {
                   afficher_interroclaire = true;
                   afficher_homeclaire = false;
               } else if (stick == 0 && axis == 0 && pos < -deadzone && current_bg == 2) {
                   afficher_interroclaire = false;
                   afficher_homeclaire = true;
               }
           }





          break;
        }
         case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:{
            int _a = 0;
            int b = 1;
            int x = 2;
            int y = 3;
            int start = 7;
            int _bouton = event->joystick.button;
            if( _bouton == _a && afficher_homeclaire == true ) {
               afficher_homeclaireGros = true;
            }
            if( _bouton == _a &&  current_bg == 1 ) {
                afficherJouer = true;
            }
            if( _bouton == _a && afficher_interroclaire  == true && current_bg == 0) {

                afficher_interroclaireGros = true;
            }
            printf("%d", event->joystick.button);
            if( _bouton == start && pauseActive == false && current_bg == 2) {
                dessin = 1;
                pauseActive = true;
                afficher_homeclaire = true;
            }else if ( _bouton == start && pauseActive == true  && current_bg == 2) {
                dessin = 0;
                pauseActive = false;
                afficher_homeclaire = false;
                afficher_interroclaire= false;
            }
            if (current_bg == 2 && _bouton == _a) {
                current_bg = 4;
                dessin = 0;
                temps = 1;
                p=1;
            }
            if (  _bouton == a && current_bg != 0  && current_bg != 1  && current_bg != 2  && current_bg != 3) {
                if ((jump==0 && (g==0 && ((y2-100-x2+400<=100) && (y2-100-x2+400>=-100)) || y2>=750) || (y2-300<=10 && y2-300>=-10 && (x1>=100 && x1<=600) && current_bg == 4  || (y2-525>=-10 && y2-525<=10 && x1>=400 && x1<=500) || y2>=650 || (y2-400>=-10 && y2-400<=10 && x1>=800 && x1<=1000 || (y2-600>=-10 && y2-600<=10 && x1>=1150 && x1<=1285)) && current_bg == 5))) {
                    jump=25;
                }
                else if ((y2-500<=10 && y2-500>=-10 && (x2>=150 && x2<=540) || y2-400<=10 && y2-400>=-10 && (x2>=500 && x2<=785) || y2-535<=10 && y2-535>=-10 && (x2>=750 && x2<=1050) || y1>=550 || y2-400<=10 && y2-400>=-10 && (x2>=920 && x2<=1050) || y2-575<=10 && y2-575>=-10 && (x2>=1000 && x2<=1350)) && current_bg == 8) {
                    jump=25;
                }
                else if (g==0 && current_bg == 7 &&(y2-450<=10 && y2-450>=-10 && (x2>=180 && x2<=1450))) {
                    jump=25;
                }
                else if (current_bg == 9 && g==0 &&(y2-300<=10 && y2-300>=-10 && (x2>=180 && x2<=1450) ||(y2-180<=10 && y2-180>=-10 && (x2>=250 && x2<=450)) || (y2-170<=10 && y2-170>=-10 && (x2>=520 && x2<=690)) || (y2-165<=10 && y2-165>=-10 && (x2>=750 && x2<=950)) || (y2-115<=10 && y2-115>=-10 && (x2>=950 && x2<=1400)) )) {
                    jump=25;
                }
                else if (g==0 && current_bg == 10 &&(y2-630<=10 && y2-630>=-10 || (y2-430<=10 && y2-430>=-10 && (x2>=1200 && x2<=1400)))) {
                    jump=25;
                }
                else if (g==0 && current_bg ==6 &&((y2-520<=10 && y2-520>=-10 && (x2>=180 && x2<=1450)) || (y2-430<=10 && y2-430>=-10 && (x2>=950 && x2<=1350)) || (y2-150<=10 && y2-150>=-10 && (x2>=550 && x2<=850)) || (y2-265<=10 && y2-265>=-10 && (x2>=250 && x2<=510)))) {
                    jump=40;
                }
            }

            if( _bouton == x && current_bg != 0  && current_bg != 1  && current_bg != 2  && current_bg != 3 )
            break;
        }

        case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP: {
            int a_ = 0;
            int b = 1;
            int x = 2;
            int y = 3;
            int bouton_ = event->joystick.button;

            if( bouton_ == a_ && afficher_homeclaire == true  ) {
                current_bg = 1;
                afficher_homeclaireGros = false;
                afficher_homeclaire = false;

            }else if( bouton_ == a_ && afficher_interroclaire == true  ) {
                current_bg = 3;
                afficher_interroclaireGros = false;



            }
            if( bouton_ == a_ &&  current_bg == 1 && afficherJouer == true ) {
                afficherJouer = false;
                current_bg = 2;
                pauseActive = false;
                dessin = 0;
            }





            break;
        }
        case ALLEGRO_EVENT_DISPLAY_RESIZE: {
            h = event->display.height;
            w = event->display.width;
            al_flip_display();
            break;
        }
        case ALLEGRO_EVENT_KEY_DOWN: {
            switch(event->keyboard.keycode) {
                case ALLEGRO_KEY_T: {
                    show_text = !show_text;
                    break;
                }
                case ALLEGRO_KEY_ENTER: {
                    if (x1>=1100 && y1<= 350) glace-=1;
                    break;
                }
                case ALLEGRO_KEY_SPACE: {
                    for (int i=0; i<10; i++) {
                        if (!tabF[i].isActive) {
                            tabF[i].isActive = true;
                            tabF[i].direction=j1.direction;
                            tabF[i].x1 =x1+25;
                            tabF[i].x2 =x2-25;
                            tabF[i].y1 =y1+25;
                            tabF[i].y2 =y2-25;
                        }
                    }
                    break;
                }
                case ALLEGRO_KEY_A: {
                    if ((jump==0 && (g==0 && ((y2-100-x2+400<=100) && (y2-100-x2+400>=-100)) || y2>=750) || (y2-300<=10 && y2-300>=-10 && (x1>=100 && x1<=600) && current_bg == 4  || (y2-525>=-10 && y2-525<=10 && x1>=400 && x1<=500) || y2>=650 || (y2-400>=-10 && y2-400<=10 && x1>=800 && x1<=1000 || (y2-600>=-10 && y2-600<=10 && x1>=1150 && x1<=1285)) && current_bg == 5))) {
                        jump=25;
                    }
                    else if ((y2-500<=10 && y2-500>=-10 && (x2>=150 && x2<=540) || y2-400<=10 && y2-400>=-10 && (x2>=500 && x2<=785) || y2-535<=10 && y2-535>=-10 && (x2>=750 && x2<=1050) || y1>=550 || y2-400<=10 && y2-400>=-10 && (x2>=920 && x2<=1050) || y2-575<=10 && y2-575>=-10 && (x2>=1000 && x2<=1350)) && current_bg == 8) {
                        jump=25;
                    }
                    else if (g==0 && current_bg == 7 &&(y2-450<=10 && y2-450>=-10 && (x2>=180 && x2<=1450))) {
                        jump=25;
                    }
                    else if (current_bg == 9 && g==0 &&(y2-300<=10 && y2-300>=-10 && (x2>=180 && x2<=1450) ||(y2-180<=10 && y2-180>=-10 && (x2>=250 && x2<=450)) || (y2-170<=10 && y2-170>=-10 && (x2>=520 && x2<=690)) || (y2-165<=10 && y2-165>=-10 && (x2>=750 && x2<=950)) || (y2-115<=10 && y2-115>=-10 && (x2>=950 && x2<=1400)) )) {
                        jump=25;
                    }
                    else if (g==0 && current_bg == 10 &&(y2-630<=10 && y2-630>=-10 || (y2-430<=10 && y2-430>=-10 && (x2>=1200 && x2<=1400)))) {
                        jump=25;
                    }
                    else if (g==0 && current_bg ==6 &&((y2-520<=10 && y2-520>=-10 && (x2>=180 && x2<=1450)) || (y2-430<=10 && y2-430>=-10 && (x2>=950 && x2<=1350)) || (y2-150<=10 && y2-150>=-10 && (x2>=550 && x2<=850)) || (y2-265<=10 && y2-265>=-10 && (x2>=250 && x2<=510)))) {
                        jump=40;
                    }
                    break;
                }
                case ALLEGRO_KEY_Z: {
                    z=1;
                    break;
                }
                case ALLEGRO_KEY_Q: {
                    q=1;
                    break;
                }
                case ALLEGRO_KEY_S: {
                    s=1;
                    break;
                }
                case ALLEGRO_KEY_D: {
                    d=1;
                    break;
                }
            }
            break;
        }
        case ALLEGRO_EVENT_KEY_UP: {
            switch(event->keyboard.keycode) {
                case ALLEGRO_KEY_Z: {
                    z=0;
                    break;
                }
                case ALLEGRO_KEY_Q: {
                    q=0;
                    break;
                }
                case ALLEGRO_KEY_S: {
                    s=0;
                    break;
                }
                case ALLEGRO_KEY_D: {
                    d=0;
                    break;
                }
            }
            break;
        }
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
            if (current_bg == 1 && clicDansBouton(event->mouse.x, event->mouse.y, bouton)) current_bg = 2;

            if (current_bg == 2 && clicDansBouton(event->mouse.x,event->mouse.y,niveau1)) {
                current_bg = 4;
                dessin = 0;
                temps = 1;
                p=1;
            }
            if (clicDansBouton(event->mouse.x, event->mouse.y, question) && current_bg != 11) {
                pinterrogation(backgrounds,file,fermerQuestion,&a,current_bg);
                a=1;
            }
            if (clicDansBouton(event->mouse.x, event->mouse.y, maison) && current_bg != 11) {
                current_bg = 0;
                dessin = 1;
                temps = 0;
                p=0;
            }
            if (clicDansBouton(event->mouse.x,event->mouse.y,volume) && current_bg != 11) show_audio_interface(file,music_instance,&running,&is_sound_muted);

            if (clicDansBouton(event->mouse.x,event->mouse.y,pause) && current_bg != 11) {
                if (p==1) dessin = 1;
                else dessin = 0;
            }
            if (clicDansBouton(event->mouse.x,event->mouse.y,jouer )&& current_bg == 11) {
                current_bg = 0;
            }
            break;
        }
        case ALLEGRO_EVENT_DISPLAY_CLOSE: {
            fini = true;
            }
    }
}
    for(int i=0;i < NB_BACKGROUNDS; i++) al_destroy_bitmap(backgrounds[i]);
    al_destroy_bitmap(son_coupe);
    al_destroy_bitmap(son_actif);
    al_destroy_bitmap(play);
    al_destroy_bitmap(stop);
    al_destroy_bitmap(poireau);
    al_destroy_bitmap(tomD);
    al_destroy_bitmap(tomG);
    al_destroy_bitmap(glacon_avant);
    al_destroy_bitmap(horloge1);
    al_destroy_bitmap(horloge2);
    al_destroy_bitmap(horloge3);
    al_destroy_bitmap(horloge4);
    al_destroy_bitmap(home);
    al_destroy_bitmap(quest);
    al_destroy_bitmap(fin_reussi);
    al_destroy_bitmap(jauge1);
    al_destroy_bitmap(jauge2);
    al_destroy_bitmap(jauge3);
    al_destroy_bitmap(jauge4);
    al_destroy_bitmap(tomate_fin);
    al_destroy_bitmap(jouer_fin);
    al_destroy_font(font);
    al_destroy_display(fenetre);
    al_destroy_event_queue(file);
    al_destroy_timer(timer_dessin);
    al_destroy_timer(timer_pause);
    al_destroy_sample_instance(music_instance);
    al_destroy_mixer(mixer);
    al_destroy_voice(voice);
    al_destroy_sample(music);
    al_destroy_font(font);
    al_uninstall_audio();
    free(event);
    free(tabF);
    free(tabObst);
    return 0;
}
