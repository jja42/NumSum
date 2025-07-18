#include "button.h"
#include <stdio.h>

void exit_button_func(Game* game, void* data)
{
    exit_game(game);
}

void main_scene_button_func(Game* game, void* data)
{
    main_scene(game);
}

void start_menu_button_func(Game* game, void* data){
    start_scene(game);
}

//Just Prints for Now. Not Yet Connected
void info_button_func(Game* game, void* data)
{
    printf("Button is Working\n");
}

void grid_entity_button_func(Game* game, void* data){
    Num* n = (Num*)data;
    printf("Number clicked: %d. At Position [%d,%d]\n", n->value, n->x, n->y);
}

Button* init_button(char* button_name, int x, int y, int w, int h, char* text, TTF_Font* font,  OnClick click_function, SDL_Renderer* ren, void* data)
{
    Button* button = malloc(sizeof(Button));

    //Handle Malloc Error
    if(button == NULL){
         printf("Failed to allocate Button.\n");
         return NULL;
    }

    //Set our params
    button->name = button_name;
    button->x_pos = x;
    button->y_pos = y;
    button->width = w;
    button->height = h;
    button->on_click = click_function;
    button->data = data;
    button->interactible = true;

    //Create Text Surface and Texture
    SDL_Color black = {0, 0, 0};
    SDL_Surface* text_surface = TTF_RenderText_Blended(font, text, black);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ren, text_surface);

    //Get these for centering
    int text_width = text_surface->w;
    int text_height = text_surface->h;

    //FREE
    SDL_FreeSurface(text_surface);

    //Create a rect
    SDL_Rect text_rect = {
    button->x_pos + (button->width - text_width) / 2,
    button->y_pos + (button->height - text_height) / 2,
    text_width,
    text_height};

    //Assign our text refs here for rendering later
    button->text_texture = text_texture;
    button->text_rect = text_rect;

    return button;
    
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

    //Render the text for our button
    SDL_RenderCopy(renderer, button->text_texture, NULL, &button->text_rect);
}

//Free Text Texture and Button
void free_button(Button *button){
    SDL_DestroyTexture(button->text_texture);
    free(button);
}
