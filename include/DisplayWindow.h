#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include <SDL2/SDL.h>

class DisplayWindow {
public:
    DisplayWindow();
    DisplayWindow(const char* title, int width, int height);

    static bool InitSDL();

    int GetWidth();
    int GetHeight();

    bool CheckClosed();

    void Show(unsigned char * frame);

    ~DisplayWindow();
private:
    int width;
    int height;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif