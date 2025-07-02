#include "game_manager.h"
#include <stdlib.h>
#include "button.h"
#include <SDL2/SDL.h>
#include <stdio.h>

void add_entity(Game *game, entity_s *entity)
{
    list_add(game->entities, entity);
}

Game* init_game(){
    Game* game = malloc(sizeof(Game));
    game->state = START,
    game->entities = new_list(100);
    return game;
}

void render_entities(SDL_Renderer* renderer, Game* game){
    //loop through entities
    for(int i = 0; i< game->entities->capacity; i++){
        //ignore NULL
        if(game->entities->data[i] == NULL){
            continue;
        }
        //get entity
        entity_s *entity = (entity_s*)game->entities->data[i];
        //look at entity type
        switch (entity->type)
        {
        //if button, render button
        case BUTTON:
            render_button(renderer,(Button*) entity->data);
            break;
        
        default:
            break;
        }
    }
}

void check_entity_click(Game* game, int mouseX, int mouseY){
    //loop through entities
    for(int i = 0; i< game->entities->capacity; i++){
        //ignore NULL
        if(game->entities->data[i] == NULL){
            continue;
        }
        //get entity
        entity_s *entity = (entity_s*)game->entities->data[i];
        //look at entity type
        switch (entity->type)
        {
        //if button, check position against pos and size
        case BUTTON:
            Button* button = (Button*) entity->data;
            //check x bounds
            if(mouseX <= button->x_pos + button->width && mouseX >= button->x_pos){
                //check y bounds
                if(mouseY <= button->y_pos + button->height && mouseY >= button->y_pos){
                    //if within bounds, call on_click
                    button->on_click(button);
                }
            }
            break;
        
        default:
            break;
        }
    }
}

void free_entities(Game* game){
    //loop through entities
    for(int i = 0; i< game->entities->capacity; i++){
        //ignore NULL
        if(game->entities->data[i] == NULL){
            continue;
        }
        //get entity
        entity_s *entity = (entity_s*)game->entities->data[i];
        //look at entity type
        switch (entity->type)
        {
        //if button, check position against pos and size
        case BUTTON:
            Button* button = (Button*) entity->data;
            free_button(button);
            break;
        default:
            break;
        }
    }
}

//Free any lingering entity data
//Then clear entity list
void clear_scene(Game* game){
    free_entities(game);
    clear_list(game->entities);
}

//As Clear Scene but frees the list for cleanup
void free_game(Game* game){
    free_entities(game);
    free_list(game->entities);
}