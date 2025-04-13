#include <SDL2/SDL.h>
#include <iostream>

#include "DisplayWindow.h"

// Window dimensions
const int WINDOW_WIDTH = 1366;
const int WINDOW_HEIGHT = 768;

int main(int argc, char* argv[]){
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize SDL2: " << SDL_GetError() << std::endl;
        return -1;
    }

    TDWindow* mainWindow = new TDWindow(
        "3d render",
        WINDOW_WIDTH, WINDOW_HEIGHT
    );

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events in the queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Loop iteration
    }

    delete mainWindow;

    return 0;
}