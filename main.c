#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#include "game_manager.h"
#include "list.h"

//Declare Game in Global Scope
Game game;

int main(int argc, char* argv[]) {

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create SDL Window
    SDL_Window* win = SDL_CreateWindow("Mouse Input Example",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    //Create SDL Renderer
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    //Create a Button for Testing
    MenuButton testbutton = {    
    .x_pos = 250,
    .y_pos = 200,
    .interactible = true,
    .name = "Test",
    .width = 300,
    .height = 150,
    .on_click = game_info_button
};

    //Initialize an Entity
    entity_s ent = {BUTTON, &testbutton};

    init_game(&game);
    add_entity(&game,&ent);

    bool running = true;
    SDL_Event e;

    //Game Loop
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                //If we close out
                case SDL_QUIT:
                    running = false;
                    break;

                //Click Handling
                case SDL_MOUSEBUTTONDOWN:
                    //printf("Mouse button %d pressed at (%d, %d)\n", e.button.button, e.button.x, e.button.y);

                    //On Left Click
                    if(e.button.button == 1){ 
                        check_entity_click(&game,e.button.x, e.button.y);
                    }
                    break;
            }
        }

        //Set Background Color
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

        //Clear what has been rendered
        SDL_RenderClear(ren);

        //Render our Button, Not Yet Responsive
        //render_button(ren, &testbutton);
        render_entities(ren, &game);

        //Refresh our Render
        SDL_RenderPresent(ren);

         //16 ms delay for our CPU's sake
        SDL_Delay(16);
    }

    printf("Closing Game\n");

    //Clean Up and Exit
    free_list(game.entities);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
