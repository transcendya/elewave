#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "types.h"

class WaveMap;

class WaveManager {
public:
    WaveManager();
    WaveManager(WaveMap * waveMap);

    void CreateFixedPoint(
        Coor x, Coor y, Displ displ,
        ColorCoor red, ColorCoor green, ColorCoor blue
    );
    void CreateFixedRect(
        Coor x, Coor y, Distance w, Distance h, Displ displ,
        ColorCoor red, ColorCoor green, ColorCoor blue
    );
    void CreateFixedCircle(
        Coor x, Coor y, Distance radius, Displ displ,
        ColorCoor red, ColorCoor green, ColorCoor blue
    );

    void Update();

    ~WaveManager();
private:
    WaveMap * waveMap;

    //To avoid multiple calls to WaveMap, a few pointers and variables are kept duplicate here
    unsigned int * waveStep;
    DeltaT * waveDeltaTime;
};

#endif