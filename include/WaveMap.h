#ifndef WAVE_MAP_H
#define WAVE_MAP_H

#include "types.h"

class WaveMap {
public:
    WaveMap();
    WaveMap(MapDim width, MapDim height);

    void GetPositiveColor(
        ColorCoor& positiveRed,
        ColorCoor& positiveGreen,
        ColorCoor& positiveBlue
    );
    void GetNeutralColor(
        ColorCoor& neutralRed,
        ColorCoor& neutralGreen,
        ColorCoor& neutralBlue
    );
    void GetNegativeColor(
        ColorCoor& negativeRed,
        ColorCoor& negativeGreen,
        ColorCoor& negativeBlue
    );
    Displ GetMaxDispl();
    Displ * GetDisplMap();
    Displ * GetDisplMapBefore();
    Speed * GetSpeedMap();
    bool * GetIgnoreMap();
    ColorCoor * GetColorMap();
    ColorCoor * GetCroppedColorMap();
    void GetMapDimensions(
        MapDim& width,
        MapDim& height
    );
    void GetColorMapDimensions(
        WDim& cmWidth,
        WDim& cmHeight
    );

    void SetPositiveColor(
        ColorCoor positiveRed,
        ColorCoor positiveGreen,
        ColorCoor positiveBlue
    );
    void SetNeutralColor(
        ColorCoor neutralRed,
        ColorCoor neutralGreen,
        ColorCoor neutralBlue
    );
    void SetNegativeColor(
        ColorCoor negativeRed,
        ColorCoor negativeGreen,
        ColorCoor negativeBlue
    );
    void SetMaxDispl(Displ maxDispl);
    
    void SetWaveSpeedValue(Speed waveSpeed);
    void SetDeltaSpace(Distance deltaSpace);
    void SetDeltaTime(DeltaT deltaTime);

    void UpdateDisplMaps();
    void UpdateColorMap();

    void PokeMap(Coor x, Coor y, Displ displ);
    void PokeMapBefore(Coor x, Coor y, Displ displ);
    void EnableIgnorePoint(Coor x, Coor y);
    void DisableIgnorePoint(Coor x, Coor y);

    ~WaveMap();
private:
    void InitColors();
    void InitDisplMaps();
    void InitSpeedMap();
    void InitIgnoreMap();
    void InitColorMap();

    MapDim width;
    MapDim height;

    WDim cmWidth;
    WDim cmHeight;

    Displ maxDispl;

    //Positive color (wave value at one)
    ColorCoor positiveRed;
    ColorCoor positiveGreen;
    ColorCoor positiveBlue;

    //Neutral color (wave value at zero)
    ColorCoor neutralRed;
    ColorCoor neutralGreen;
    ColorCoor neutralBlue;

    //Negative color (wave value at minus one)
    ColorCoor negativeRed;
    ColorCoor negativeGreen;
    ColorCoor negativeBlue;

    //Matrix of wave at t=0 and t=-1
    Displ * displMap;
    Displ * displMapBefore;

    //Matrix of wave speeds
    Speed * speedMap;

    //Matrix of ignore points
    bool * ignoreMap;

    ColorCoor * colorMap;

    //Wave specifications
    Distance deltaSpace;
    DeltaT deltaTime;
};

#endif