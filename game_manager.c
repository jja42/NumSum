#include "game_manager.h"
#include <stdio.h>
#include "ui_manager.h"
#include "scene_manager.h"

void add_entity(Game *game, entity_s *entity)
{
    list_add(game->entities, entity);
}

entity_s* init_entity(Entity_Type type, void* entity_data, int active, char* name){
    //Initialize an Entity
    entity_s *ent = malloc(sizeof(entity_s));
    //Handle Malloc Error
    if(ent == NULL){
         printf("Failed to allocate Entity.\n");
         return NULL;
    }

    ent->name = strdup(name);
    ent->type = type;
    ent->data = entity_data;

    if(active == 0){
        ent->active = false;
    }
    else{
        ent->active = true;
    }

    ent->interactible = true;

    return ent;
}

Game* init_game(SDL_Renderer* renderer){
    Game* game = malloc(sizeof(Game));
    //Handle Malloc Error
    if(game == NULL){
         printf("Failed to allocate Game.\n");
         return NULL;
    }
    game->mode = START;
    game->paused = false;
    game->entities = new_list(100);
    game->renderer = renderer;
    game->ui_manager = init_ui();
    game->scene_manager = init_scene_management();
    game->lives = 4;
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
            //Do Not Render if Inactive
            if(entity->active == 0){
                continue;
            }
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
            //if text panel, render text panel
            case GRIDENTITY:
                ui_render_grid_entity(renderer, entity->data);
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
            //Do not click Inactive Entities
            if(!entity->active){
                continue;
            }
            //look at entity type
            switch (entity->type)
            {
            //if button, check position against pos and size
            case BUTTON:
                if(ui_check_click(entity, mouseX, mouseY)){
                    ui_click_button(entity, game);
                    return;
                }
                break;
            case GRIDENTITY:
                if(ui_check_click(entity, mouseX, mouseY)){
                    ui_click_grid_entity(entity,game);
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
                free_button(entity);
                break;
             //if text panel, free text panel
            case TEXTPANEL:
                free_text_panel(entity);
                break;
            case GRIDENTITY:
                free_grid_entity(entity);
            default:
                break;
            }
            free(entity->name);
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
    game->mode = END;
}

void main_scene(Game* game){
    load_scene_name(MAIN_GAME, game);
}

void resume_game(Game* game){
    game->mode = START;
}

void pause_game(Game* game){
    game->mode = START;
}

void start_scene(Game* game){
    load_scene_name(START_MENU, game);
}

void info_popup(Game* game, bool active){
    if(active){
        entity_set_all_inactive(game);
        entity_set_active("InfoPanel", game);
        entity_set_active("CloseButton", game);
    }
    else{
        entity_set_all_active(game);
        entity_set_inactive("InfoPanel", game);
        entity_set_inactive("CloseButton", game);
    }
}

entity_s* get_entity(char* name, Game* game){
    //loop through entities
    for(int i = 0; i< game->entities->capacity; i++){
        //ignore NULL
        if(game->entities->data[i] != NULL){
            //get entity
            entity_s *entity = (entity_s*)game->entities->data[i];
            if(strcmp(entity->name, name) == 0){
                return entity;
            }
        }
    }
}

void entity_set_active(char* name, Game* game){
    get_entity(name, game)->active = true;
}

void entity_set_inactive(char* name, Game* game){
    get_entity(name, game)->active = false;
}

void entity_set_all_active(Game* game){
    //loop through entities
    for(int i = 0; i< game->entities->capacity; i++){
        //ignore NULL
        if(game->entities->data[i] != NULL){
            //get entity
            entity_s *entity = (entity_s*)game->entities->data[i];
            entity->active = true;
        }
    }
}

void entity_set_all_inactive(Game* game){
    //loop through entities
    for(int i = 0; i< game->entities->capacity; i++){
        //ignore NULL
        if(game->entities->data[i] != NULL){
            //get entity
            entity_s *entity = (entity_s*)game->entities->data[i];
            entity->active = false;
        }
    }
}


void mark_mode(Game* game){
    game->mode = MARK;

    entity_s* ent = get_entity("MarkButton", game);
    ui_change_panel_border(ui_get_panel(ent),ui_get_color("GOLD"));

    ent = get_entity("EraseButton", game);
    ui_change_panel_border(ui_get_panel(ent),ui_get_color("BLUE"));
}

void erase_mode(Game* game){
    game->mode = ERASE;

    entity_s* ent = get_entity("EraseButton", game);
    ui_change_panel_border(ui_get_panel(ent),ui_get_color("GOLD"));

    ent = get_entity("MarkButton", game);
    ui_change_panel_border(ui_get_panel(ent),ui_get_color("BLUE"));
}

void recalculate_sums(Game* game){
    update_sums(game->grid);

    for(int i = 0; i<game->grid->size; i++){
        char name[20];
        snprintf(name, sizeof(name), "Row Sum #%d", i);

        remove_entity(name,game);

        snprintf(name, sizeof(name), "Col Sum #%d", i);

        remove_entity(name,game);
    }

    generate_sums(game);  
}

void remove_entity(char* name, Game* game){
    //loop through entities
    for(int i = 0; i< game->entities->capacity; i++){
        //ignore NULL
        if(game->entities->data[i] != NULL){
            //get entity
            entity_s *entity = (entity_s*)game->entities->data[i];
            if(strcmp(entity->name, name) == 0){
                switch (entity->type)
                {
                //if button, free button
                case BUTTON:
                    free_button(entity);
                    break;
                //if text panel, free text panel
                case TEXTPANEL:
                    free_text_panel(entity);
                    break;
                case GRIDENTITY:
                    free_grid_entity(entity);
                default:
                    break;
                }
                free(entity->name);
                free(entity);
                game->entities->data[i] = NULL;
                return;
            }
        }
    }

    printf("Could Not Find Entity with Name: %s\n", name);
}

void check_victory(Game* game){
    if(check_grid_complete(game->grid)){
        printf("You Win! :)\n");
    }
}

void check_loss(Game* game){
    if(game->lives <= 0){
        printf("Game Over Man :(\n");
    }
}

void lose_life(Game* game){
    game->lives -= 1;
    entity_s* ent = get_entity("Lives",game);
    char text[40]; 
    snprintf(text, sizeof(text), "  You Have\n   %d Lives\n Remaining",game->lives);
    ui_update_panel_text(ui_get_panel(ent),text,ARIAL,game);
}