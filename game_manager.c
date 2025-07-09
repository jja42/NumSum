#include "game_manager.h"
#include <stdio.h>
#include "ui_manager.h"
#include "scene_manager.h"

void add_entity(Game *game, entity_s *entity)
{
    list_add(game->entities, entity);
}

entity_s* init_entity(Entity_Type type, void* entity_data){
    //Initialize an Entity
    entity_s *ent = malloc(sizeof(entity_s));
    //Handle Malloc Error
    if(ent == NULL){
         printf("Failed to allocate Entity.\n");
         return NULL;
    }
    ent->type = BUTTON;
    ent->data = entity_data;
    return ent;
}

Game* init_game(SDL_Renderer* renderer){
    Game* game = malloc(sizeof(Game));
    //Handle Malloc Error
    if(game == NULL){
         printf("Failed to allocate Game.\n");
         return NULL;
    }
    game->state = START,
    game->entities = new_list(100);
    game->renderer = renderer;
    game->ui_manager = init_ui();
    game->scene_manager = init_scene_management();
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
            ui_click_button(entity, mouseX, mouseY);
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
    free_scenes(game->scene_manager);
    free(game);
}