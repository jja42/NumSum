#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "ui_elements.h"
#include "game_manager.h"

typedef struct Game Game;

typedef struct entity_s entity_s;

typedef enum FONT{
ARIAL
} FONT;

//Returns a font from our list of fonts
TTF_Font* get_font(FONT font, UI* ui);

//Adds a font to our list
void add_font(TTF_Font* font, UI* ui);

//Setup the UI object
UI* init_ui();

//Free our fonts. CLOSE EM.
void free_ui(UI* ui);

//Called by Scene Manager to add a button. Creates a Button and adds it to Game Manager's entities
void add_button_to_scene(char* button_name, int x, int y, int w, int h, char* text, FONT font_name, OnClick click_function, Game* game, void* data, int active);

//Wrapper for Rendering Buttons so that Game Manager can defer this to the UI Manager
void ui_render_button(SDL_Renderer* ren, void* button_data);

//Wrapper for Clicking Buttons so that the Game Manager can defer this to the UI Manager
void ui_click_button(entity_s* entity, Game* game);

bool ui_check_button(entity_s* entity, int mouseX, int mouseY);

//return a font given a string
FONT parse_font(char* font);

//return a button function given a string
OnClick parse_button_function(char* function);

//Called by Scene Manager to add a Text Panel. Creates a Text Panel and adds it to Game Manager's entities. Also sets active.
void add_text_panel_to_scene(char* name, int x, int y, int w, int h, char* text, FONT font_name, Game* game, int active);

//Wrapper for Rendering Text Panels so that Game Manager can defer this to the UI Manager
void ui_render_text_panel(SDL_Renderer* ren, void* text_panel_data);

#endif