#include <iostream>

#include "types.h"

#include "DisplayWindow.h"
#include "WaveMap.h"

// Map dimensions
const MapDim MAP_WIDTH = 1366;
const MapDim MAP_HEIGHT = 768;

int main(int argc, char* argv[]){
    (void)argc;
    (void)argv;

    if(!DisplayWindow::InitSDL()){
        return -1;
    }

    WaveMap* waveMap = new WaveMap(
        MAP_WIDTH, MAP_HEIGHT
    );

    WDim window_width, window_height;
    waveMap->GetCroppedMapDimensions(
        window_width, window_height
    );

    DisplayWindow* mainWindow = new DisplayWindow(
        "3d render",
        window_width, window_height
    );

    // Main loop
    unsigned long i = 0;
    while (true) {
        if(i % 100 == 0){
            std::cout << "Poked!" << std::endl;
            waveMap->PokeMap(100, 100, 1.0f);
        }
        i++;
        if(mainWindow->CheckClosed()){
            break;
        }

        waveMap->UpdateWaveMaps();
        waveMap->UpdateColorMap();
        Color * frame = waveMap->GetCroppedColorMap();
        mainWindow->Show(frame);
    }

    delete mainWindow;

    return 0;
}