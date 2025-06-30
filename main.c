#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Mouse Input Example",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    printf("Success!\n");

        bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEMOTION:
                    printf("Mouse moved to (%d, %d)\n", e.motion.x, e.motion.y);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    printf("Mouse button %d pressed at (%d, %d)\n",
                           e.button.button, e.button.x, e.button.y);
                    break;

                case SDL_MOUSEBUTTONUP:
                    printf("Mouse button %d released at (%d, %d)\n",
                           e.button.button, e.button.x, e.button.y);
                    break;

                case SDL_MOUSEWHEEL:
                    printf("Mouse wheel: (%d, %d)\n",
                           e.wheel.x, e.wheel.y);
                    break;
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
    }
}
