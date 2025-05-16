#include "son1.h"

Button create_button(float x, float y, float width, float height, const char* text,ALLEGRO_COLOR bouton_color,ALLEGRO_COLOR text_color) {
    Button button;
    button.x = x;
    button.y = y;
    button.width = width;
    button.height = height;
    button.color = bouton_color;
    button.border_color = bouton_color;
    button.text_color = text_color;
    button.text = text;
    return button;
}

Slider create_slider(float x, float y, float width, float height, float min_value, float max_value, float initial_value) {
    Slider slider;
    slider.x = x;
    slider.y = y;
    slider.width = width;
    slider.height = height;
    slider.min_value = min_value;//
    slider.max_value = max_value;
    slider.current_value = initial_value;
    slider.rail_color = al_map_rgb(150, 150, 150);
    slider.handle_color = al_map_rgb(200, 200, 200);
    slider.is_dragging = false;
    return slider;
}

bool is_mouse_over_button(Button button, int mouse_x, int mouse_y) {
    return (mouse_x >= button.x &&
            mouse_x <= button.x + button.width &&
            mouse_y >= button.y &&
            mouse_y <= button.y + button.height);
}

bool is_mouse_over_slider_handle(Slider slider, int mouse_x, int mouse_y) {
    float handle_pos = slider.x + (slider.current_value - slider.min_value) /
                      (slider.max_value - slider.min_value) * slider.width;
    float handle_radius = slider.height * 1.5;

    return (mouse_x >= handle_pos - handle_radius && mouse_x <= handle_pos + handle_radius &&
            mouse_y >= slider.y - handle_radius && mouse_y <= slider.y + handle_radius);
}

bool is_mouse_over_slider_rail(Slider slider, int mouse_x, int mouse_y) {
    int click_area = slider.height * 2;
    return (mouse_x >= slider.x && mouse_x <= slider.x + slider.width &&
            mouse_y >= slider.y - click_area && mouse_y <= slider.y + click_area);
}

void update_slider_value(Slider *slider, int mouse_x) {
    float relative_x = mouse_x - slider->x;
    if (relative_x < 0) relative_x = 0;
    if (relative_x > slider->width) relative_x = slider->width;

    slider->current_value = slider->min_value + (relative_x / slider->width) * (slider->max_value - slider->min_value);
}

void draw_button(Button button, ALLEGRO_FONT *font) {
    al_draw_filled_rectangle(button.x, button.y, button.x + button.width, button.y + button.height, button.color);
    al_draw_rectangle(button.x, button.y, button.x + button.width, button.y + button.height, button.border_color, 2.0);

    if (font) {
        float text_width = al_get_text_width(font, button.text);
        float text_height = al_get_font_line_height(font);

        float text_x = button.x + (button.width - text_width) / 2;
        float text_y = button.y + (button.height - text_height) / 2;

        al_draw_text(font, button.text_color, text_x, text_y, 0, button.text);
    }
}

void draw_slider(Slider slider, ALLEGRO_FONT *font, const char *label) {
    al_draw_filled_rectangle(slider.x, slider.y - slider.height/2, slider.x + slider.width, slider.y + slider.height/2, slider.rail_color);

    float filled_width = (slider.current_value - slider.min_value) / (slider.max_value - slider.min_value) * slider.width;
    al_draw_filled_rectangle(slider.x, slider.y - slider.height/2, slider.x + filled_width, slider.y + slider.height/2, al_map_rgb(0, 150, 255));

    float handle_pos = slider.x + filled_width;
    float handle_radius = slider.height * 1.5;

    al_draw_filled_circle(handle_pos, slider.y, handle_radius, slider.handle_color);
    al_draw_circle(handle_pos, slider.y, handle_radius, al_map_rgb(100, 100, 100), 2);

    if (font) {
        al_draw_text(font, al_map_rgb(255, 255, 255), slider.x, slider.y - 40, 0, label);

        char value_text[20];
        snprintf(value_text, sizeof(value_text), "%.0f%%", slider.current_value * 100);
        al_draw_text(font, al_map_rgb(255, 255, 255),
                    slider.x + slider.width + 20, slider.y - 10, 0, value_text);
    }
}

bool check_sound_muted(ALLEGRO_SAMPLE_INSTANCE* music_instance) {
    // Obtenir le niveau actuel du volume
    float current_gain = al_get_sample_instance_gain(music_instance);

    // Vérifier si le son est coupé (volume à zéro ou presque zéro)
    if (current_gain <= 0.1) {
        return true; // Le son est coupé
    }else{
        return false; // Le son n'est pas coupé
    }
}

void show_audio_interface(ALLEGRO_EVENT_QUEUE *file,ALLEGRO_SAMPLE_INSTANCE *music_instance,bool* running,bool* is_sound_muted) {


    Button back_button = create_button(
        (WIDTH - BUTTON_WIDTH) / 2,
        HEIGHT - 100,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        "retour",
        al_map_rgb(50, 50, 50),
        al_map_rgb(255, 255, 255)
    );

    Slider volume_slider = create_slider(
        (WIDTH - SLIDER_WIDTH) / 2,
        HEIGHT / 2,
        SLIDER_WIDTH,
        SLIDER_HEIGHT,
        0.0, 1.0, al_get_sample_instance_gain(music_instance)
    );

    bool audio_interface_active = true;

    while (audio_interface_active && *running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(file, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                *running = false;
                audio_interface_active = false;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    audio_interface_active = false;
                }
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if (event.mouse.button == 1) {
                    if (is_mouse_over_button(back_button, event.mouse.x, event.mouse.y)) {
                        audio_interface_active = false;
                    }
                    else if (is_mouse_over_slider_handle(volume_slider, event.mouse.x, event.mouse.y)) {
                        volume_slider.is_dragging = true;
                    }
                    else if (is_mouse_over_slider_rail(volume_slider, event.mouse.x, event.mouse.y)) {
                        update_slider_value(&volume_slider, event.mouse.x);
                        al_set_sample_instance_gain(music_instance, volume_slider.current_value);
                        volume_slider.is_dragging = true;
                    }
                }
                break;
            }

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                if (event.mouse.button == 1) {
                    volume_slider.is_dragging = false;
                }
                break;
            }

            case ALLEGRO_EVENT_MOUSE_AXES: {
                if (volume_slider.is_dragging) {
                    update_slider_value(&volume_slider, event.mouse.x);
                    al_set_sample_instance_gain(music_instance, volume_slider.current_value);
                }
                break;
            }
        }
        *is_sound_muted = check_sound_muted(music_instance); // la
        al_clear_to_color(al_map_rgb(0, 0, 0));
        draw_slider(volume_slider, NULL, "Volume");
        draw_button(back_button, NULL);

        al_flip_display();
    }
}
