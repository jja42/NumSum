#include "game_manager.h"
#include <stdlib.h>
#include "menu.h"
#include <SDL2/SDL.h>
#include <stdio.h>

void add_entity(Game *game, entity_s *entity)
{
    list_add(game->entities, entity);
}

void init_game(Game* game){
    game->state = START,
    game->entities = new_list(100);
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
            render_button(renderer,(MenuButton*) entity->data);
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
            MenuButton* button = (MenuButton*) entity->data;
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
            MenuButton* button = (MenuButton*) entity->data;
            free_button(button);
            break;
        default:
            break;
        }
    }
}