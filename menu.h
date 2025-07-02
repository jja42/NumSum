#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct MenuButton;

//A Button!
//It has a name, a position, a size, even a bool and a function
typedef struct MenuButton{
char* name;
int x_pos;
int y_pos;
int width;
int height;
bool interactible;
void (*on_click)(struct MenuButton* self);
char* button_text;
SDL_Texture* text_texture;
SDL_Rect text_rect;
} MenuButton;

void include_test();

//Will call game_manager's exit function. 
void exit_game_button(MenuButton* self);

//Will call game_manager's start function.
void start_game_button(MenuButton* self);

//Will call game_manager's start function
void game_info_button(MenuButton* self);

//Renders a Button to the Screen with a render and button info
void render_button(SDL_Renderer* renderer, MenuButton* button);

//Take a newly created button and set it up, also creates a text texture
void init_button(MenuButton* button, char* button_name, int x, int y, int w, int h, char* text, TTF_Font* font, void (*on_click)(struct MenuButton* self), SDL_Renderer* ren);

//Frees Button Data
void free_button(MenuButton *button);

#endif