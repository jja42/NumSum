#ifndef MENU_H
#define MENU_H

#include <stdbool.h>


void include_test();

typedef struct {
char* name;
int x_pos;
int y_pos;
int width;
int height;
bool interactible;
void (*on_click)(MenuButton* self);
} MenuButton;


#endif