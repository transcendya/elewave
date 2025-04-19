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
    Coor x, Coor y, Distance w, Distance h, Displ displ
){
    Displ * displMap = waveMap->GetDisplMap();
    Displ * displMapBefore = waveMap->GetDisplMapBefore();
    bool * ignoreMap = waveMap->GetIgnoreMap();

    MapDim width, height;
    waveMap->GetMapDimensions(width, height);

    for(unsigned int i = y; i < y + h; i++){
        for(unsigned int j = x; j < x + w; j++){
            unsigned int currentPos = i * width + j;
            
            displMap[currentPos] = displ;
            displMapBefore[currentPos] = displ;
            ignoreMap[currentPos] = true;
        }
    }
}

WaveManager::~WaveManager(){
    delete waveMap;
    waveMap = nullptr;
}