#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "entity.h"

//Various states for the game that will trigger functions when swapped
typedef enum {
START,
RUNNING,
LOADING,
PAUSED,
END
} GameState;

//Contains our Game State and a List of Entities
//We will use this to track our game and loop through our entities
typedef struct {
GameState state;
entity_s** entities;
} Game;

Game* get_game();

//Will change game state to PAUSED which will stop timers and bring up pause menu
void pause_game(Game* game);

//Will change game state to RUNNING and will close Pause Menu
void resume_game(Game* game);

//Will change game state to RUNNING and transition us from the Start Menu into Loading
void start_game(Game* game);

//Will change game state to LOADING which will start Level Gen and Prepare Grid
void load_game(Game* game);

//Will change game state to END which will cause game to stop running and exit
void exit_game(Game* game);

//Will change game state to START and bring us to the start menu
void start_menu(Game* game);

//Will toggle on and off an info popup
void info_popup();

#endif