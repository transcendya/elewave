#include <iostream>

#include "types.h"

#include "DisplayWindow.h"
#include "WaveMap.h"

// Map dimensions
const MapDim MAP_WIDTH = 500;
const MapDim MAP_HEIGHT = 500;

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
    waveMap->GetColorMapDimensions(
        window_width, window_height
    );

    DisplayWindow* mainWindow = new DisplayWindow(
        "3d render",
        window_width, window_height
    );

    waveMap->SetDeltaTime(0.001f);

    for(int i = 200; i < 210; i++){
        for(int j = 200; j < 210; j++){
            waveMap->PokeMap(i, j, -1.0f);
        }
    }

    for(int i = 200; i < 210; i++){
        for(int j = 290; j < 300; j++){
            waveMap->PokeMap(i, j, -1.0f);
        }
    }

    // Main loop
    while (true) {
        if(mainWindow->CheckClosed()){
            break;
        }

        waveMap->UpdateWaveMaps();
        waveMap->UpdateColorMap();
        Color * frame = waveMap->GetColorMap();
        mainWindow->Show(frame);
    }

    delete mainWindow;

    return 0;
}