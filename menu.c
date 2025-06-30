#include "menu.h"
#include <stdio.h>
#include <SDL2/SDL.h>

//Just to make sure my includes are working. They are.
void include_test(){
    printf("Include Worked\n");
}

void exit_game_button(struct MenuButton *self)
{
}

void start_game_button(struct MenuButton *self)
{
}

//Just Prints for Now. Not Yet Connected
void game_info_button(struct MenuButton *self)
{
    printf("Button is Working");
}

void render_button(SDL_Renderer* renderer, MenuButton* button) {
    //Creates an SDL Rect for the Button's Border First
    SDL_Rect border = { button->x_pos - 7.5, button->y_pos - 7.5, button->width + 15, button->height + 15 };
    
    //Sets Border Color (Blue)
    SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
    SDL_RenderFillRect(renderer, &border);

    //Crreat Rect for Button Itself
    SDL_Rect rect = { button->x_pos, button->y_pos, button->width, button->height };

    //Sets Color (White)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    //Draws Rect onto Render
    SDL_RenderDrawRect(renderer, &rect);
}
