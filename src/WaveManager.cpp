#include "WaveManager.h"

#include "WaveMap.h"

WaveManager::WaveManager(){
    waveMap = nullptr;
}

WaveManager::WaveManager(WaveMap * waveMap){
    this->waveMap = waveMap;
}

void WaveManager::CreateFixedPoint(Coor x, Coor y, Displ displ){
    waveMap->PokeMap(x,y,displ);
    waveMap->PokeMapBefore(x,y,displ);
    waveMap->EnableIgnorePoint(x,y);
}

WaveManager::~WaveManager(){
    delete waveMap;
    waveMap = nullptr;
}