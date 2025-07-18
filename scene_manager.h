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
    LOSS,
    VICTORY
}Scene_Name;

//Switch Statement with enum to load correct scene
void load_scene_name(Scene_Name scene_name, Game* game);

//Clears current scene. Then loads a scene from Json Objects stored in Scene Manager's scenes
void load_scene(char* name, Game* game);

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
list_t* load_scene_file(char* filepath);

//load all of the objects in a scene into the game
void load_scene_objects(Scene* scene, list_t* scene_objects, Game* game);

//Get our game's grid, initialize the entities needed
void setup_grid_entities(Game* game);

#endif