#include "scene_manager.h"
#include "ui_manager.h"
#include "json_parser.h"

void load_scene(Scene scene_name, Game* game){
    switch (scene_name)
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

    add_button_to_scene("StartButton", 250, 50, 200, 100, "Start", ARIAL, game_info_button, game);
    add_button_to_scene("InfoButton", 250, 200, 200, 100, "Info", ARIAL, game_info_button, game);
    add_button_to_scene("ExitButton", 250, 350, 200, 100, "Exit", ARIAL, exit_game_button, game);
}

void load_scene_manifest(char* filepath, SceneManager* manager){
    list_t* objects = read_json_into_objects(filepath);
    if(objects == NULL){
        printf("Failed to read JSON.\n");
         return;
    }
    print_json(objects);
}

void free_scenes(SceneManager* scene_management){

}

SceneManager* init_scene_management(){
    SceneManager* manager = malloc(sizeof(SceneManager));
    //Handle Malloc Error
    if(manager == NULL){
         printf("Failed to allocate Scene Manager.\n");
         return NULL;
    }
    return manager;
}