#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "game_manager.h"

typedef struct Game Game;

typedef struct{
    char* name;
    list_t* objects;
} Scene;

//Switch Statement with enum to load correct scene
void load_scene(char* scene_name, Game* game);

//Loads the start menu with its buttons and text
void load_start_menu(Game* game);

//Clear the Entire "Scene" by removing all entities
void clear_scene(Game* game);

//load the scene manifest json file
void load_scene_manifest(char* filepath, SceneManager* scene_management);

//free the scene manager and its scenes
void free_scenes(SceneManager* scene_management);

//Initialize the Scene Manager
SceneManager* init_scene_management();

#endif