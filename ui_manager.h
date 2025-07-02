#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "list.h"

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

#endif