#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game_manager.h"

//A Button!
//It has a name, a position, a size, even a bool and a function
//Now also holds text and text accessories
typedef struct Button{
char* name;
int x_pos;
int y_pos;
int width;
int height;
bool interactible;
void (*on_click)(Game* game);
char* button_text;
SDL_Texture* text_texture;
SDL_Rect text_rect;
} Button;

//Will call game_manager's exit function. 
void exit_game_button(Game* game);

//Will call game_manager's start function.
void start_game_button(Game* game);

//Will call game_manager's start function
void game_info_button(Game* game);

//Renders a Button to the Screen with a render and button info
void render_button(SDL_Renderer* renderer, Button* button);

//Create a new button and set it up, also creates a text texture
Button* init_button(char* button_name, int x, int y, int w, int h, char* text, TTF_Font* font, void (*click_function)(Game* game), SDL_Renderer* ren);

//Frees Button Data
void free_button(Button *button);

#endif