#include "WaveManager.h"

#include "WaveMap.h"
#include "functions.h"

WaveManager::WaveManager(){
    waveMap = nullptr;
    
    waveStep = nullptr;
    waveDeltaTime = nullptr;
}

WaveManager::WaveManager(WaveMap * waveMap){
    this->waveMap = waveMap;
    
    waveStep = waveMap->GetStepPointer();
    waveDeltaTime = waveMap->GetDeltaTimePointer();
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
            unsigned int currentColorPos = 3 * ((i - 1) * cmWidth + j - 1);
            
            displMap[currentPos] = displ;
            displMapBefore[currentPos] = displ;
            ignoreMap[currentPos] = true;

            colorMap[currentColorPos] = red;
            colorMap[currentColorPos + 1] = green;
            colorMap[currentColorPos + 2] = blue;
        }
    }
}

void WaveManager::CreateFixedCircle(
    Coor x, Coor y, Distance radius, Displ displ,
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

    Distance radiusSquared = radius * radius;

    for(unsigned int i = y - radius; i < y + radius; i++){
        for(unsigned int j = x - radius; j < x + radius; j++){
            //If point is outside the circle skip it
            if(euclideanSquared(j, i, x, y) > radiusSquared){ continue; }
            
            unsigned int currentPos = i * width + j;
            unsigned int currentColorPos = 3 * ((i - 1) * cmWidth + j - 1);
            
            displMap[currentPos] = displ;
            displMapBefore[currentPos] = displ;
            ignoreMap[currentPos] = true;

            colorMap[currentColorPos] = red;
            colorMap[currentColorPos + 1] = green;
            colorMap[currentColorPos + 2] = blue;
        }
    }
}

void WaveManager::Update(){
}

WaveManager::~WaveManager(){
    delete waveMap;
    waveMap = nullptr;
}