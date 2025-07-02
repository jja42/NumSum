#include "button.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "scene_manager.h"
#include "game_manager.h"
#include "entity.h"

void load_scene(Scene scene, Game* game){
    switch (scene)
    {
    case START_MENU:
        load_start_menu(game);
        break;
    default:
        break;
    }
}

//Free any lingering entity data
//Then clear entity list
void clear_scene(Game* game){
    free_entities(game);
    clear_list(game->entities);
}

void load_start_menu(Game* game){
    clear_scene(game);
    //Create a Button for Testing
    Button* testbutton = malloc(sizeof(Button));
    TTF_Font* font = get_font(ARIAL, game->ui_manager);
    init_button(testbutton, "Test", 250, 250, 300, 150, "Click Me", font, game_info_button, game->renderer);

    //Initialize an Entity
    entity_s *ent = malloc(sizeof(entity_s));
    ent->type = BUTTON;
    ent->data = testbutton;

    add_entity(game, ent);
}