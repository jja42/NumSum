#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#include "game_manager.h"
#include "list.h"
#include <SDL2/SDL_ttf.h>

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

    SDL_Color black = {0, 0, 0};
    SDL_Surface* text_surface = TTF_RenderText_Blended(font, "Click Me", black);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ren, text_surface);

    int text_width = text_surface->w;
    int text_height = text_surface->h;

    SDL_FreeSurface(text_surface);




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

SDL_Rect text_rect = {
    testbutton.x_pos + (testbutton.width - text_width) / 2,
    testbutton.y_pos + (testbutton.height - text_height) / 2,
    text_width,
    text_height
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

        SDL_RenderCopy(ren, text_texture, NULL, &text_rect);

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
    SDL_DestroyTexture(text_texture);
    SDL_Quit();
}
