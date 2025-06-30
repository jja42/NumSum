#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <SDL2/SDL.h>

struct MenuButton;

typedef struct {
char* name;
int x_pos;
int y_pos;
int width;
int height;
bool interactible;
void (*on_click)(struct MenuButton* self);
} MenuButton;

void include_test();

void exit_game_button(struct MenuButton* self);

void start_game_button(struct MenuButton* self);

void game_info_button(struct MenuButton* self);

void render_button(SDL_Renderer* renderer, MenuButton* button);

#endif