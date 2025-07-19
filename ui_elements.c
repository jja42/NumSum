#include "ui_elements.h"
#include <stdio.h>
#include "ui_manager.h"

void exit_button_func(Game* game)
{
    exit_game(game);
}

void start_button_func(Game* game)
{
    select_scene(game);
}

void start_menu_button_func(Game* game){
    start_scene(game);
}

void open_info_button_func(Game* game)
{
    info_popup(game, true);
}

void close_info_button_func(Game* game)
{
    info_popup(game, false);
}

void mark_button_func(Game* game){
    mark_mode(game);
}

void erase_button_func(Game* game){
    erase_mode(game);
}

void init_grid_3(Game* game){
    init_grid(game,3);
    main_scene(game);
}

void init_grid_4(Game* game){
    init_grid(game,4);
    main_scene(game);
}

void init_grid_5(Game* game){
    init_grid(game,5);
    main_scene(game);
}

void init_grid_6(Game* game){
    init_grid(game,6);
    main_scene(game);
}

void init_grid_7(Game* game){
    init_grid(game,7);
    main_scene(game);
}

void init_grid_8(Game* game){
    init_grid(game,8);
    main_scene(game);
}

void grid_entity_click(Game* game, entity_s* ent){
    GridEntity* g_ent = (GridEntity*)ent->data;
    //printf("Number clicked: %d. At Position [%d,%d]. Is Valid: %d\n", g_ent->num->value, g_ent->x, g_ent->y, g_ent->num->is_valid);
    if(game->mode == MARK){
        if(g_ent->num->is_valid){
            //Highlight Correct Answer
            ui_change_panel_border(g_ent->panel,GOLD);
            //Mark
            g_ent->num->is_marked = true;
            ent->interactible = false;
            //Update Sums
            recalculate_sums(game);
            //check if we've completed the grid
            check_victory(game);
        }
        else{
            //printf("Attempted to mark an Invalid Number. :(\n");
            lose_life(game);
            ui_change_panel_border(g_ent->panel,RED);
            check_loss(game);
        }
    }
    if(game->mode == ERASE){
        if(g_ent->num->is_valid){
            //printf("Attempted to Erase a Valid Number. :(\n");
            lose_life(game);
            ui_change_panel_border(g_ent->panel,RED);
            check_loss(game);
        }
        else{
            ui_change_panel_border(g_ent->panel,BLUE);
            ui_update_panel_text(g_ent->panel," ",ARIAL,game);
            ent->interactible = false;
        }
    }
}

Button* init_button(TextPanel* t, OnClick click_function)
{
    Button* button = malloc(sizeof(Button));

    //Handle Malloc Error
    if(button == NULL){
         printf("Failed to allocate Button.\n");
         return NULL;
    }

    //Set our params
    button->on_click = click_function;
    button->panel = t;

    return button;
    
}

GridEntity* init_grid_entity(TextPanel* t, int x, int y, Num* n){
    GridEntity* g_ent = malloc(sizeof(GridEntity));

    if(g_ent == NULL){
         printf("Failed to allocate Grid Entity.\n");
         return NULL;
    }

    g_ent->panel = t;
    g_ent->x = x;
    g_ent->y = y;
    g_ent->num = n;

    return g_ent;
}

TextPanel* init_text_panel(int x, int y, int w, int h, char* text, FONT font_name, Game* game, Color border_color){
    TextPanel* text_panel = malloc(sizeof(TextPanel));

    //Handle Malloc Error
    if(text_panel == NULL){
         printf("Failed to allocate Text Panel.\n");
         return NULL;
    }

    TTF_Font* font = get_font(font_name, game->ui_manager);

    SDL_Renderer* ren = game->renderer;

    //Set our params
    text_panel->x_pos = x;
    text_panel->y_pos = y;
    text_panel->width = w;
    text_panel->height = h;
    text_panel->border_color = border_color;

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

void render_text_panel(SDL_Renderer* renderer, TextPanel* text_panel){
    //Creates an SDL Rect for the Text Panel's Border First
    SDL_Rect border = { text_panel->x_pos - 5, text_panel->y_pos - 5, text_panel->width + 10, text_panel->height + 10};
    
    //Sets Border Color (Green)
    switch (text_panel->border_color)
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
void free_button(entity_s *ent){
    Button* button = (Button*)ent->data;
    SDL_DestroyTexture(button->panel->text_texture);
    free(button->panel);
    free(button);
}

//Free Text Texture and Text Panel
void free_text_panel(entity_s *ent){
    TextPanel* text_panel = (TextPanel*)ent->data;
    SDL_DestroyTexture(text_panel->text_texture);
    free(text_panel);
}

void free_grid_entity(entity_s *ent){
    GridEntity* g_ent = (GridEntity*)ent->data;
    SDL_DestroyTexture(g_ent->panel->text_texture);
    free(g_ent->panel);
    free(g_ent);
}