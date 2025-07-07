#include "scene_manager.h"
#include "ui_manager.h"

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

    add_button_to_scene("StartButton", 250, 50, 200, 100, "Start", ARIAL, game_info_button, game);
    add_button_to_scene("InfoButton", 250, 200, 200, 100, "Info", ARIAL, game_info_button, game);
    add_button_to_scene("ExitButton", 250, 350, 200, 100, "Exit", ARIAL, game_info_button, game);
}