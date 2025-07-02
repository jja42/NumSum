#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "game_manager.h"

typedef enum{
    START_MENU,
    MAIN_GAME,
    HELP,
    LOSS,
    VICTORY
} Scene;

//Switch Statement with enum to load correct scene
void load_scene(Scene scene, Game* game);

//Loads the start menu with its buttons and text
void load_start_menu(Game* game);

//Clear the Entire "Scene" by removing all entities
void clear_scene(Game* game);

#endif