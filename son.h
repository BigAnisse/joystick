#ifndef SON1_H
#define SON1_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 1500
#define HEIGHT 700
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define SLIDER_WIDTH 400
#define SLIDER_HEIGHT 20

typedef struct {
    float x;
    float y;
    float width;
    float height;
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR border_color;
    ALLEGRO_COLOR text_color;
    char* text;
} Button;

typedef struct {
    float x;
    float y;
    float width;
    float height;
    float min_value;
    float max_value;
    float current_value;
    ALLEGRO_COLOR rail_color;
    ALLEGRO_COLOR handle_color;
    bool is_dragging;
} Slider;//

Button create_button(float x, float y, float width, float height, const char *text,ALLEGRO_COLOR bouton_color,ALLEGRO_COLOR text_color);
Slider create_slider(float x, float y, float width, float height, float min_value, float max_value, float initial_value);
bool is_mouse_over_button(Button button, int mouse_x, int mouse_y);
bool is_mouse_over_slider_handle(Slider slider, int mouse_x, int mouse_y);
bool is_mouse_over_slider_rail(Slider slider, int mouse_x, int mouse_y);
void update_slider_value(Slider *slider, int mouse_x);
void draw_button(Button button, ALLEGRO_FONT *font);
void draw_slider(Slider slider, ALLEGRO_FONT *font, const char *label);
bool check_sound_muted(ALLEGRO_SAMPLE_INSTANCE *music_instance);
void show_audio_interface(ALLEGRO_EVENT_QUEUE *file,ALLEGRO_SAMPLE_INSTANCE *music_instance,bool* running,bool* is_sound_muted);

#endif // SON1_H
