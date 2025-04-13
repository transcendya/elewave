#include <iostream>

#include "types.h"

#include "DisplayWindow.h"

// Window dimensions
const WDim WINDOW_WIDTH = 1366;
const WDim WINDOW_HEIGHT = 768;

int main(int argc, char* argv[]){
    (void)argc;
    (void)argv;

    if(!DisplayWindow::InitSDL()){
        return -1;
    }

    DisplayWindow* mainWindow = new DisplayWindow(
        "3d render",
        WINDOW_WIDTH, WINDOW_HEIGHT
    );

    // Main loop
    while (true) {
        if(mainWindow->CheckClosed()){
            break;
        }

        // Loop iteration
    }

    delete mainWindow;

    return 0;
}