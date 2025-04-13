#include "DisplayWindow.h"

#include <iostream>

DisplayWindow::DisplayWindow(){
    width = 0;
    height = 0;
}

DisplayWindow::DisplayWindow(const char* title, int width, int height){
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

int DisplayWindow::GetWidth(){
    return width;
}

int DisplayWindow::GetHeight(){
    return height;
}

void DisplayWindow::Show(unsigned char * frame){
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