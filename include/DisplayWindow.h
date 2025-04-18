#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "types.h"

#include <SDL2/SDL.h>

class DisplayWindow {
public:
    DisplayWindow();
    DisplayWindow(const char* title, WDim width, WDim height);

    static bool InitSDL();

    WDim GetWidth();
    WDim GetHeight();

    bool CheckClosed();

    void Show(ColorCoor * frame);

    ~DisplayWindow();
private:
    WDim width;
    WDim height;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif