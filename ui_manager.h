#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "list.h"

typedef struct{
list_t* fonts;
} UI;

TTF_Font get_font();

#endif