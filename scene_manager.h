#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "game_manager.h"

typedef struct Game Game;

typedef struct{
    char* name;
    list_t* objects;
} Scene;

typedef enum{
    START_MENU,
    MAIN_GAME,
    HELP,
    LOSS,
    VICTORY
}Scene_Name;

//Switch Statement with enum to load correct scene
void load_scene_name(Scene_Name scene_name, Game* game);

//Loads the start menu with its buttons and text
void load_start_menu(Game* game);

//Clear the Entire "Scene" by removing all entities
void clear_scene(Game* game);

//load the scene manifest json file
void load_scene_manifest(char* filepath, SceneManager* manager);

//free the scene manager and its scenes
void free_scenes(SceneManager* manager);

//free an individual scene
void free_scene(Scene* scene);

//Initialize the Scene Manager
SceneManager* init_scene_management();

//read through scene manifest objects and initiliaze our scene manager's scenes list
void read_scene_manifest(list_t* manifest, SceneManager* manager);

//read a scene from a filepath and return a list of its json objects
list_t* load_scene(char* filepath);

#endif