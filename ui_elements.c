#include "ui_elements.h"
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

void open_info_button_func(Game* game, void* data)
{
    info_popup(game, true);
}

void close_info_button_func(Game* game, void* data)
{
    info_popup(game, false);
}

void mark_button_func(Game* game, void* data){
    mark_mode(game);
}

void erase_button_func(Game* game, void* data){
    erase_mode(game);
}

void grid_entity_button_func(Game* game, void* data){
    Num* n = (Num*)data;
    printf("Number clicked: %d. At Position [%d,%d]. Is Valid: %d\n", n->value, n->x, n->y, n->is_valid);
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

TextPanel* init_text_panel(char* name, int x, int y, int w, int h, char* text, TTF_Font* font, SDL_Renderer* ren){
    TextPanel* text_panel = malloc(sizeof(TextPanel));

    //Handle Malloc Error
    if(text_panel == NULL){
         printf("Failed to allocate Text Panel.\n");
         return NULL;
    }

    //Set our params
    text_panel->name = name;
    text_panel->x_pos = x;
    text_panel->y_pos = y;
    text_panel->width = w;
    text_panel->height = h;

    //Create Text Surface and Texture
    SDL_Color black = {0, 0, 0};
    SDL_Surface* text_surface = TTF_RenderText_Blended_Wrapped(font, text, black,0);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ren, text_surface);

    //Get these for centering
    int text_width = text_surface->w;
    int text_height = text_surface->h;

    //FREE
    SDL_FreeSurface(text_surface);

    //Create a rect
    SDL_Rect text_rect = {
    text_panel->x_pos + (text_panel->width - text_width) / 2,
    text_panel->y_pos + (text_panel->height - text_height) / 2,
    text_width,
    text_height};

    //Assign our text refs here for rendering later
    text_panel->text_texture = text_texture;
    text_panel->text_rect = text_rect;

    return text_panel;
}

void render_button(SDL_Renderer* renderer, Button* button) {
    //Creates an SDL Rect for the Button's Border First
    SDL_Rect border = { button->x_pos - 5, button->y_pos - 5, button->width + 10, button->height + 10};
    
    //Sets Border Color (Blue)
    switch (button->border_color)
    {
    case BLUE:
        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
        break;
    case RED:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        break;
    case GOLD:
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
        break;
    case GREEN:
        SDL_SetRenderDrawColor(renderer, 144, 238, 144, 255);
        break;
    default:
        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
        break;
    }
    SDL_RenderFillRect(renderer, &border);

    //Create Rect for Button Itself
    SDL_Rect rect = { button->x_pos, button->y_pos, button->width, button->height };

    //Sets Color (White)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    //Draws Rect onto Render
    SDL_RenderDrawRect(renderer, &rect);

    //Render the text for our button
    SDL_RenderCopy(renderer, button->text_texture, NULL, &button->text_rect);
}

void render_text_panel(SDL_Renderer* renderer, TextPanel* text_panel){
    //Creates an SDL Rect for the Text Panel's Border First
    SDL_Rect border = { text_panel->x_pos - 5, text_panel->y_pos - 5, text_panel->width + 10, text_panel->height + 10};
    
    //Sets Border Color (Green)
    SDL_SetRenderDrawColor(renderer, 144, 238, 144, 255);
    SDL_RenderFillRect(renderer, &border);

    //Create Rect for Text Panel Itself
    SDL_Rect rect = { text_panel->x_pos, text_panel->y_pos, text_panel->width, text_panel->height };

    //Sets Color (White)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    //Draws Rect onto Render
    SDL_RenderDrawRect(renderer, &rect);

    //Render the text for our Text Panel
    SDL_RenderCopy(renderer, text_panel->text_texture, NULL, &text_panel->text_rect);
}

//Free Text Texture and Button
void free_button(Button *button){
    SDL_DestroyTexture(button->text_texture);
    free(button);
}

//Free Text Texture and Text Panel
void free_text_panel(TextPanel *text_panel){
    SDL_DestroyTexture(text_panel->text_texture);
    free(text_panel);
}
