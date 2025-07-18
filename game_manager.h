#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SDL2/SDL.h>
#include "list.h"
#include "num.h"

//Various states for the game that will trigger functions when swapped
typedef enum {
RUNNING,
PAUSED,
END
} GameState;

//Holds our fonts. 
//May also hold images and such if used
typedef struct{
list_t* fonts;
} UI;

//Holds our scenes
typedef struct{
    list_t* scenes;
} SceneManager;


//Contains our Game State and a List of Entities
//We will use this to track our game and loop through our entities
typedef struct Game{
GameState state;
list_t* entities;
SDL_Renderer* renderer;
UI* ui_manager;
SceneManager* scene_manager;
Grid* grid;
} Game;

typedef enum {
BUTTON,
TEXTPANEL
} Entity_Type;

//Container Type to Loop through for Game Manager
typedef struct entity_s{
char* name;
Entity_Type type;
void* data;
bool active;
} entity_s;


//Will change game state to PAUSED which will stop timers and bring up pause menu
void pause_game(Game* game);

//Will change game state to RUNNING and will close Pause Menu
void resume_game(Game* game);

//Will change game state to RUNNING and transition us from the Start Menu into the Main Scene
void main_scene(Game* game);

//Will change game state to END which will cause game to stop running and exit
void exit_game(Game* game);

//Will change game state to START and bring us to the start scene
void start_scene(Game* game);

//Will toggle on and off an info popup
void info_popup(Game* game, bool active);

//Adds an entity onto the entity stack
void add_entity(Game* game, entity_s* entity);

//Initializes the game
Game* init_game(SDL_Renderer* renderer);

//Loops through Entities and calls render function based on type
void render_entities(Game* game);

//Loops through Entities and checks if their position is within Mouse Click
void check_entity_click(Game* game, int mouseX, int mouseY);

//Loop through Entities, call any associated Free Functions
void free_entities(Game* game);

//Frees all of the Game Struct's Data
void free_game(Game* game);

//Create and Return and Entity
entity_s* init_entity(Entity_Type type, void* entity_data, int active, char* name);

//Ends the Game by changing our state to END
void exit_game(Game* game);

//Find an entity and set it active
void entity_set_active(char* name, Game* game);

//Find an entity and set it inactive
void entity_set_inactive(char* name, Game* game);

//Set all entities active
void entity_set_all_active(Game* game);

//Set all entities inactive
void entity_set_all_inactive(Game* game);

#endif