#include "game_manager.h"
#include "button.h"
#include <SDL2/SDL.h>

void load_start_menu(Game* game, SDL_Renderer* ren){
    clear_list(game);
    //Create a Button for Testing
    Button testbutton;
    //init_button(&testbutton, "Test",250, 250, 300, 150, "Click Me", font, game_info_button, ren);

    //Initialize an Entity
    entity_s ent = {BUTTON, &testbutton};
    add_entity(&game,&ent);
}