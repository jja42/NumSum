#include "button.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void exit_game_button(Button *self)
{
}

void start_game_button(Button *self)
{
}

//Just Prints for Now. Not Yet Connected
void game_info_button(Button *self)
{
    printf("Button is Working\n");
}

void init_button(Button* button, char* button_name, int x, int y, int w, int h, char* text, TTF_Font* font, void (*click_function)(struct Button* self), SDL_Renderer* ren)
{
    button->name = button_name;
    button->x_pos = x;
    button->y_pos = y;
    button->width = w;
    button->height = h;
    button->on_click = click_function;
    button->interactible = true;

    SDL_Color black = {0, 0, 0};
    SDL_Surface* text_surface = TTF_RenderText_Blended(font, text, black);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ren, text_surface);

    int text_width = text_surface->w;
    int text_height = text_surface->h;

    SDL_FreeSurface(text_surface);

    SDL_Rect text_rect = {
    button->x_pos + (button->width - text_width) / 2,
    button->y_pos + (button->height - text_height) / 2,
    text_width,
    text_height};

    button->text_texture = text_texture;
    button->text_rect = text_rect;
    
}

void render_button(SDL_Renderer* renderer, Button* button) {
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

    SDL_RenderCopy(renderer, button->text_texture, NULL, &button->text_rect);
}

//Destroys Allocated Text Texture
void free_button(Button *button){
    SDL_DestroyTexture(button->text_texture);
}
