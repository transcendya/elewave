#include <iostream>

#include "types.h"

#include "DisplayWindow.h"
#include "WaveMap.h"
#include "WaveManager.h"

// Map dimensions
const MapDim MAP_WIDTH = 1000;
const MapDim MAP_HEIGHT = 1000;

int main(int argc, char* argv[]){
    (void)argc;
    (void)argv;

    if(!DisplayWindow::InitSDL()){
        return -1;
    }

    WaveMap* waveMap = new WaveMap(
        MAP_WIDTH, MAP_HEIGHT
    );
    WaveManager* waveManager = new WaveManager(
        waveMap
    );
    waveManager->CreateFixedPoint(500,500,-1.0f);

    WDim window_width, window_height;
    waveMap->GetColorMapDimensions(
        window_width, window_height
    );

    DisplayWindow* mainWindow = new DisplayWindow(
        "3d render",
        window_width, window_height
    );

    waveMap->SetDeltaTime(0.1f);

    // Main loop
    while (true) {
        if(mainWindow->CheckClosed()){
            break;
        }

        waveMap->UpdateDisplMaps();
        waveMap->UpdateColorMap();
        ColorCoor * frame = waveMap->GetColorMap();
        mainWindow->Show(frame);
    }

    delete mainWindow;

    return 0;
}