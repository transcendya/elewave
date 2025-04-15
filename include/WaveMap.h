#ifndef WAVE_MAP_H
#define WAVE_MAP_H

#include "types.h"

class WaveMap {
public:
    WaveMap();
    WaveMap(MapDim width, MapDim height);

    void GetPositiveColor(
        Color& positiveRed,
        Color& positiveGreen,
        Color& positiveBlue
    );
    void GetNeutralColor(
        Color& neutralRed,
        Color& neutralGreen,
        Color& neutralBlue
    );
    void GetNegativeColor(
        Color& negativeRed,
        Color& negativeGreen,
        Color& negativeBlue
    );
    Displ GetMaxDispl();
    Color * GetColorMap();
    Color * GetCroppedColorMap();
    void GetMapDimensions(
        MapDim& width,
        MapDim& height
    );
    void GetCroppedMapDimensions(
        MapDim& width,
        MapDim& height
    );

    void SetPositiveColor(
        Color positiveRed,
        Color positiveGreen,
        Color positiveBlue
    );
    void SetNeutralColor(
        Color neutralRed,
        Color neutralGreen,
        Color neutralBlue
    );
    void SetNegativeColor(
        Color negativeRed,
        Color negativeGreen,
        Color negativeBlue
    );
    void SetMaxDispl(Displ maxDispl);
    
    void SetWaveSpeed(Speed waveSpeed);
    void SetDeltaSpace(Distance deltaSpace);
    void SetDeltaTime(DeltaT deltaTime);

    void UpdateWaveMaps();
    void UpdateColorMap();

    void PokeMap(Coor x, Coor y, Displ displ);

    ~WaveMap();
private:
    void InitColors();
    void InitWaveMaps();
    void InitColorMap();

    MapDim width;
    MapDim height;

    Displ maxDispl;

    //Positive color (wave value at one)
    Color positiveRed;
    Color positiveGreen;
    Color positiveBlue;

    //Neutral color (wave value at zero)
    Color neutralRed;
    Color neutralGreen;
    Color neutralBlue;

    //Negative color (wave value at minus one)
    Color negativeRed;
    Color negativeGreen;
    Color negativeBlue;

    //Matrix of wave at t=0 and t=-1
    Displ * waveMap;
    Displ * waveMapBefore;

    Color * colorMap;

    //Wave specifications
    Distance deltaSpace;
    DeltaT deltaTime;
    Speed waveSpeed;
};

#endif