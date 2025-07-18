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
    ent->type = type;
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
    game->state = RUNNING,
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
        if(game->entities->data[i] != NULL){
            //get entity
            entity_s *entity = (entity_s*)game->entities->data[i];
            //look at entity type
            switch (entity->type)
            {
            //if button, render button
            case BUTTON:
                ui_render_button(renderer, entity->data);
                break;
            //if text panel, render text panel
            case TEXTPANEL:
                ui_render_text_panel(renderer, entity->data);
                break;
            default:
                break;
            }
        }
    }
}

void check_entity_click(Game* game, int mouseX, int mouseY){
    //loop through entities
    for(int i = 0; i< game->entities->capacity; i++){
        //ignore NULL
        if(game->entities->data[i] != NULL){
            //get entity
            entity_s *entity = (entity_s*)game->entities->data[i];
            //look at entity type
            switch (entity->type)
            {
            //if button, check position against pos and size
            case BUTTON:
                if(ui_check_button(entity, mouseX, mouseY)){
                    ui_click_button(entity, game);
                    return;
                }
                break;
            default:
                break;
            }
        }
    }
}

void free_entities(Game* game){
    //loop through entities
    for(int i = 0; i< game->entities->capacity; i++){
        //ignore NULL
        if(game->entities->data[i] != NULL){
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
             //if text panel, free text panel
            case TEXTPANEL:
                TextPanel* text_panel = (TextPanel*) entity->data;
                free_text_panel(text_panel);
                break;
            default:
                break;
            }
            free(entity);
        }
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

void exit_game(Game* game){
    game->state = END;
}

void main_scene(Game* game){
    load_scene_name(MAIN_GAME, game);
}

void resume_game(Game* game){
    if(game->state == PAUSED){
        game->state = RUNNING;    
    }
}

void pause_game(Game* game){
    if(game->state == RUNNING){
        game->state = PAUSED;
    }
}

void start_scene(Game* game){
    load_scene_name(START_MENU, game);
}

void info_popup(Game* game){
    load_scene_name(INFO, game);
}

