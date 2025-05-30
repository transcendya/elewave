#include "DisplayWindow.h"

#include <iostream>

DisplayWindow::DisplayWindow(){
    width = 0;
    height = 0;
}

DisplayWindow::DisplayWindow(const char* title, WDim width, WDim height){
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Quit();
        throw std::runtime_error("Error: Could not create window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Error: Could not create renderer");
    }

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        width, height
    );

    if (!texture) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Error: Could not create texture");
    }

    this->width = width;
    this->height = height;
}

bool DisplayWindow::InitSDL(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize SDL2: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

WDim DisplayWindow::GetWidth(){
    return width;
}

WDim DisplayWindow::GetHeight(){
    return height;
}

bool DisplayWindow::CheckClosed(){
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

void DisplayWindow::Show(ColorCoor * frame){
    SDL_UpdateTexture(texture, nullptr, frame, width * 3);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

DisplayWindow::~DisplayWindow(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}