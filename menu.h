#ifndef MENU_H
#define MENU_H

#include <stdbool.h>


void include_test();

void exit_game();

void start_game();

void game_info();

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


#endif