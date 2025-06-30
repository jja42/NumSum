#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <SDL2/SDL.h>

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

#endif