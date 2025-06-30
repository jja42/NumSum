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
    for(int i = 0; i< game->entities->capacity; i++){
        if(game->entities->data[i] == NULL){
            continue;
        }
        entity_s *entity = (entity_s*)game->entities->data[i];
        switch (entity->type)
        {
        case BUTTON:
            render_button(renderer,(MenuButton*) entity->data);
            break;
        
        default:
            break;
        }
    }
}