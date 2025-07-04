#include "game_manager.h"
#include <stdio.h>

void add_entity(Game *game, entity_s *entity)
{
    list_add(game->entities, entity);
}

entity_s* init_entity(Entity_Type type, void* entity_data){
    //Initialize an Entity
    entity_s *ent = malloc(sizeof(entity_s));
    ent->type = BUTTON;
    ent->data = entity_data;
    return ent;
}

Game* init_game(SDL_Renderer* renderer){
    Game* game = malloc(sizeof(Game));
    game->state = START,
    game->entities = new_list(100);
    game->renderer = renderer;
    game->ui_manager = init_ui();
    return game;
}

void render_entities(Game* game){
    SDL_Renderer* renderer = game->renderer;
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
            ui_render_button(renderer, entity->data);
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
        //if button, free button
        case BUTTON:
            Button* button = (Button*) entity->data;
            free_button(button);
            break;
        default:
            break;
        }
        free(entity);
    }
}

//Free our Entities, UI Manager and our List
void free_game(Game* game){
    free_entities(game);
    free_list(game->entities);
    free_ui(game->ui_manager);
    free(game);
}