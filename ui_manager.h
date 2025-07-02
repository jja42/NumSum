#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "list.h"
#include "button.h"

typedef enum{
ARIAL
} FONT;

typedef struct{
list_t* fonts;
} UI;

//Returns a font from our list of fonts
TTF_Font* get_font(FONT font, UI* ui);

//Adds a font to our list
void add_font(TTF_Font* font, UI* ui);

//Setup the UI object
UI* init_ui();

//Free our fonts. CLOSE EM.
void free_ui(UI* ui);

//Called by Scene Manager to add a button. Creates a Button and adds it to Game Manager's entities
void add_button_to_scene();

//Wrapper for Rendering Buttons so that Game Manager can defer this to the UI Manager
void ui_render_button(SDL_Renderer* ren, void* button_data);

#endif