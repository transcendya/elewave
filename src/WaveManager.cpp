#include "WaveManager.h"

#include "WaveMap.h"

WaveManager::WaveManager(){
    waveMap = nullptr;
}

WaveManager::WaveManager(WaveMap * waveMap){
    this->waveMap = waveMap;
}

void WaveManager::CreateFixedPoint(
    Coor x, Coor y, Displ displ,
    ColorCoor red, ColorCoor green, ColorCoor blue
){
    waveMap->PokeMap(x, y, displ);
    waveMap->PokeMapBefore(x, y, displ);
    waveMap->EnableIgnorePoint(x, y);
    waveMap->PokeColorMap(x-1, y-1, red, green, blue);
}

void WaveManager::CreateFixedRect(
    Coor x, Coor y, Distance w, Distance h, Displ displ,
    ColorCoor red, ColorCoor green, ColorCoor blue
){
    Displ * displMap = waveMap->GetDisplMap();
    Displ * displMapBefore = waveMap->GetDisplMapBefore();
    bool * ignoreMap = waveMap->GetIgnoreMap();
    ColorCoor * colorMap = waveMap->GetColorMap();

    MapDim width, height;
    waveMap->GetMapDimensions(width, height);

    MapDim cmWidth, cmHeight;
    waveMap->GetColorMapDimensions(cmWidth, cmHeight);

    for(unsigned int i = y; i < y + h; i++){
        for(unsigned int j = x; j < x + w; j++){
            unsigned int currentPos = i * width + j;
            
            displMap[currentPos] = displ;
            displMapBefore[currentPos] = displ;
            ignoreMap[currentPos] = true;
        }
    }

    for(unsigned int i = y - 1; i < y + h - 1; i++){
        for(unsigned int j = x - 1; j < x + w - 1; j++){
            unsigned int currentPos = 3 * (i * cmWidth + j);

            colorMap[currentPos] = red;
            colorMap[currentPos + 1] = green;
            colorMap[currentPos + 2] = blue;
        }
    }
}

WaveManager::~WaveManager(){
    delete waveMap;
    waveMap = nullptr;
}