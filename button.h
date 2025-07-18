#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game_manager.h"

typedef void (*OnClick)(Game* game, void* data);

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
OnClick on_click;
char* button_text;
SDL_Texture* text_texture;
SDL_Rect text_rect;
void* data;
} Button;

//Will call game_manager's exit function. 
void exit_button_func(Game* game, void* data);

//Will call game_manager's main scene function.
void main_scene_button_func(Game* game, void* data);

//Will call game_manager's start menu function
void start_menu_button_func(Game* game, void* data);

//Will display a popup
void info_button_func(Game* game, void* data);

//Renders a Button to the Screen with a render and button info
void render_button(SDL_Renderer* renderer, Button* button);

//Create a new button and set it up, also creates a text texture
Button* init_button(char* button_name, int x, int y, int w, int h, char* text, TTF_Font* font,  OnClick click_function, SDL_Renderer* ren, void* data);

//Frees Button Data
void free_button(Button *button);

//Button function for our grid entities
void grid_entity_button_func(Game* game, void* data);

#endif