#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SDL2/SDL.h>
#include "list.h"
#include "num.h"

//Various modes for the game depending on intended functionality
typedef enum {
MARK,
ERASE,
START,
END
} GameMode;

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
GameMode mode;
list_t* entities;
SDL_Renderer* renderer;
UI* ui_manager;
SceneManager* scene_manager;
Grid* grid;
bool paused;
int lives;
} Game;

typedef enum {
BUTTON,
TEXTPANEL,
GRIDENTITY
} Entity_Type;

//Container Type to Loop through for Game Manager
typedef struct entity_s{
char* name;
Entity_Type type;
void* data;
bool active;
bool interactible;
} entity_s;


//Stop timers and bring up pause menu
void pause_game(Game* game);

//Close Pause Menu
void resume_game(Game* game);

//Transition us from the Start Menu into the Main Scene
void main_scene(Game* game);

//Change game mode to END which will cause game to stop running and exit
void exit_game(Game* game);

//Bring us to the start scene
void start_scene(Game* game);

//Set our mode to mark, highlight the mark button
void mark_mode(Game* game);

//Set our mode to mark, highlight the erase button
void erase_mode(Game* game);

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

//Find an entity by name
entity_s* get_entity(char* name, Game* game);

//Find an entity and set it active
void entity_set_active(char* name, Game* game);

//Find an entity and set it inactive
void entity_set_inactive(char* name, Game* game);

//Set all entities active
void entity_set_all_active(Game* game);

//Set all entities inactive
void entity_set_all_inactive(Game* game);

//removes an entity from our entity_list
void remove_entity(char* name, Game* game);

//Update the sums in our grid and all relevant text panels
void recalculate_sums(Game* game);

//check our grid. if it's complete, we win!
bool check_victory(Game* game);

//check our lives. if we're out, we lose
bool check_loss(Game* game);

//deduct a life when we get an answer wrong
void lose_life(Game* game);

#endif