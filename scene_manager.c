#include "scene_manager.h"
#include "ui_manager.h"
#include "json_parser.h"

void load_scene_name(Scene_Name scene_name, Game* game){
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
    list_t* manifest = read_json_into_objects(filepath);
    if(manifest == NULL){
        printf("Failed to read JSON.\n");
        return;
    }
    //print_json(manifest);
    read_scene_manifest(manifest, manager);
}

list_t* load_scene(char* filepath){
    list_t* scene = read_json_into_objects(filepath);

    if(scene == NULL){
        printf("Failed to read JSON.\n");
        return NULL;
    }

    return scene;
}


void free_scenes(SceneManager* manager){
    for(int i = 0; i<manager->scenes->capacity; i++){
        if(manager->scenes->data[i] == NULL){
            continue;
        }
        else{
            free_scene(manager->scenes->data[i]);
        }
    }
    free_list(manager->scenes);
    free(manager);
}

void free_scene(Scene* scene){
    free(scene->name);
    for(int i = 0; i<scene->objects->capacity; i++){
        if(scene->objects->data[i] == NULL){
            continue;
        }
        else{
            free_json(scene->objects->data[i]);
        }
    }
    free_list(scene->objects);
    free(scene);
}

SceneManager* init_scene_management(){
    SceneManager* manager = malloc(sizeof(SceneManager));
    //Handle Malloc Error
    if(manager == NULL){
         printf("Failed to allocate Scene Manager.\n");
         return NULL;
    }

    manager->scenes = new_list(1);

    return manager;
}

void read_scene_manifest(list_t* manifest, SceneManager* manager){
    for(int i = 0; i<manifest->capacity; i++){
        if(manifest->data[i] == NULL){
            continue;
        }
        else{
            JsonObj* object = (JsonObj*) manifest->data[i];
            Scene* scene = malloc(sizeof(Scene*));

            list_add(manager->scenes,scene);
        }
    }
}