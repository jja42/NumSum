#include "menu.h"
#include <stdio.h>
#include <SDL2/SDL.h>

void include_test(){
    printf("Include Worked\n");
}

void exit_game_button(struct MenuButton *self)
{
}

void start_game_button(struct MenuButton *self)
{
}

void game_info_button(struct MenuButton *self)
{
    printf("Button is Working");
}

void render_button(SDL_Renderer* renderer, MenuButton* button) {
    SDL_Rect rect = { button->x_pos, button->y_pos, button->width, button->height };
    SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);  // blue
    SDL_RenderFillRect(renderer, &rect);

    // Optional: draw button border
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderDrawRect(renderer, &rect);
}
