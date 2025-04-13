#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include <SDL2/SDL.h>

class DisplayWindow {
public:
    DisplayWindow();
    DisplayWindow(const char* title, unsigned int width, unsigned int height);

    static bool InitSDL();

    unsigned int GetWidth();
    unsigned int GetHeight();

    bool CheckClosed();

    void Show(unsigned char * frame);

    ~DisplayWindow();
private:
    unsigned int width;
    unsigned int height;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif