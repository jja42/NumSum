#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game_manager.h"
#include "ui_manager.h"
#include "scene_manager.h"

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

    //Initialize SDL Text
    if (TTF_Init() == -1) {
    printf("TTF_Init error: %s\n", TTF_GetError());
    exit(1);
    }

    //Load Font
    TTF_Font* font = TTF_OpenFont("/mnt/c/Windows/Fonts/arial.ttf", 24);
    if (!font) {
    printf("Failed to load font: %s\n", TTF_GetError());
    }

    //Init Game Manager
    Game* game = init_game(ren);

    add_font(font, game->ui_manager);

    load_scene(START_MENU, game);

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
                        check_entity_click(game,e.button.x, e.button.y);
                    }
                    break;
            }
        }

        //Set Background Color
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

        //Clear what has been rendered
        SDL_RenderClear(ren);

        //Render our Entities
        render_entities(game);

        //Refresh our Render
        SDL_RenderPresent(ren);

         //20 ms delay for our CPU's sake
        SDL_Delay(20);
    }

    printf("Closing Game\n");

    //Clean Up and Exit
    free_game(game);
    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
