#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "types.h"

class WaveMap;

class WaveManager {
public:
    WaveManager();
    WaveManager(WaveMap * waveMap);

    void CreateFixedPoint(
        Coor x, Coor y, Displ displ
    );

    ~WaveManager();
private:
    WaveMap * waveMap;
};

#endif