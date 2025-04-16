#include "WaveMap.h"
#include "functions.h"

#include <iostream>

WaveMap::WaveMap(){
    width = 256; cmWidth = 254;
    height = 256; cmHeight = 254;

    waveSpeed = 1.0f;
    deltaSpace = 1.0f;
    deltaTime = 1.0f;

    maxDispl = 1.0f;
    
    InitColors();
    InitWaveMaps();
    InitColorMap();
}

WaveMap::WaveMap(MapDim width, MapDim height){
    this->width = width; this->cmWidth = width - 2;
    this->height = height; this->cmHeight = height - 2;

    waveSpeed = 1.0f;
    deltaSpace = 1.0f;
    deltaTime = 1.0f;

    maxDispl = 1.0f;
    
    InitColors();
    InitWaveMaps();
    InitColorMap();
}

void WaveMap::GetPositiveColor(
    Color& positiveRed, Color& positiveGreen, Color& positiveBlue
){
    positiveRed = this->positiveRed;
    positiveGreen = this->positiveGreen;
    positiveBlue = this->positiveBlue;
}

void WaveMap::GetNeutralColor(
    Color& neutralRed, Color& neutralGreen, Color& neutralBlue
){
    neutralRed = this->neutralRed;
    neutralGreen = this->neutralGreen;
    neutralBlue = this->neutralBlue;
}

void WaveMap::GetNegativeColor(
    Color& negativeRed, Color& negativeGreen, Color& negativeBlue
){
    negativeRed = this->negativeRed;
    negativeGreen = this->negativeGreen;
    negativeBlue = this->negativeBlue;
}

Displ WaveMap::GetMaxDispl(){
    return maxDispl;
}

Displ * WaveMap::GetWaveMap(){
    return waveMap;
}

void WaveMap::GetMapDimensions(
    MapDim& width,
    MapDim& height
){
    width = this->width;
    height = this->height;
}
void WaveMap::GetColorMapDimensions(
    WDim& cmWidth,
    WDim& cmHeight
){
    cmWidth = this->cmWidth;
    cmHeight = this->cmHeight;
}

Color * WaveMap::GetColorMap(){
    return colorMap;
}

void WaveMap::SetNeutralColor(
    Color neutralRed, Color neutralGreen, Color neutralBlue
){
    this->neutralRed = neutralRed;
    this->neutralGreen = neutralGreen;
    this->neutralBlue = neutralBlue;
}

void WaveMap::SetNegativeColor(
    Color negativeRed, Color negativeGreen, Color negativeBlue
){
    this->negativeRed = negativeRed;
    this->negativeGreen = negativeGreen;
    this->negativeBlue = negativeBlue;
}

void WaveMap::SetMaxDispl(Displ maxDispl){
    this->maxDispl = maxDispl;
}
void WaveMap::SetWaveSpeed(Speed waveSpeed){
    this->waveSpeed = waveSpeed;
}
void WaveMap::SetDeltaSpace(Distance deltaSpace){
    this->deltaSpace = deltaSpace;
}
void WaveMap::SetDeltaTime(DeltaT deltaTime){
    this->deltaTime = deltaTime;
}

void WaveMap::UpdateWaveMaps(){
    double spaceFactor = (waveSpeed * waveSpeed * deltaTime)/deltaSpace;
    
    for(unsigned int i = 1; i < height - 1; i++){
        for(unsigned int j = 1; j < width - 1; j++){
            unsigned int currentPos = i * width + j;

            Displ spaceContrib = waveMap[currentPos - 1] + waveMap[currentPos + 1]
                + waveMap[currentPos - width] + waveMap[currentPos + width] 
                - (4 * waveMap[currentPos]);

            spaceContrib *= spaceFactor;

            Displ displ = 2 * waveMap[currentPos] - waveMapBefore[currentPos] + spaceContrib;

            //Make sure values stay within -maxDispl and maxDispl
            if (displ > maxDispl) {displ = maxDispl;}
            else if (displ < -maxDispl) {displ = -maxDispl;}

            waveMapBefore[currentPos] = displ;
        }
    }

    Displ * temp = waveMapBefore;
    waveMapBefore = waveMap;
    waveMap = temp;
}

void WaveMap::UpdateColorMap(){
    for(unsigned int i = 0; i < cmHeight; i++){
        unsigned int waveStart = width * (i + 1) + 1;
        for(unsigned int j = 0; j < cmWidth; j++){
            Displ displ = waveMap[waveStart + j];
            unsigned int colorPos = 3 * (cmWidth * i + j);

            if(displ > 0.0f){
                interpolateColors(
                    neutralRed, neutralGreen, neutralBlue,
                    positiveRed, positiveGreen, positiveBlue,
                    colorMap[colorPos], colorMap[colorPos + 1], colorMap[colorPos + 2],
                    displ
                );
            }
            else{
                interpolateColors(
                    neutralRed, neutralGreen, neutralBlue,
                    negativeRed, negativeGreen, negativeBlue,
                    colorMap[colorPos], colorMap[colorPos + 1], colorMap[colorPos + 2],
                    -displ
                );
            }
        }
        
    }
}

void WaveMap::PokeMap(Coor x, Coor y, Displ displ){
    unsigned int pointIndex = y * width + x;

    waveMap[pointIndex] = displ;
}

void WaveMap::InitColors(){
    //By default, positive is red
    positiveRed = 255;
    positiveGreen = 0;
    positiveBlue = 0;
    
    //By default, neutral is white
    neutralRed = 255;
    neutralGreen = 255;
    neutralBlue = 255;

    //By default, negative is blue
    negativeRed = 0;
    negativeGreen = 0;
    negativeBlue = 255;
}

void WaveMap::InitWaveMaps(){
    unsigned int nPoints = width * height;

    waveMap = new Displ[nPoints];
    waveMapBefore = new Displ[nPoints];

    for(unsigned int i = 0; i < nPoints; i++){
        waveMap[i] = 0.0f;
        waveMapBefore[i] = 0.0f;
    }
}

void WaveMap::InitColorMap(){
    unsigned int nPoints = 3 * (width - 2) * (height - 2);

    colorMap = new Color[nPoints];

    for(unsigned int i = 0; i < nPoints; i++){
        colorMap[i] = 0;
    }
}

WaveMap::~WaveMap(){
    delete[] waveMap;
    delete[] waveMapBefore;
    delete[] colorMap;
    
    waveMap = nullptr;
    waveMapBefore = nullptr;
    colorMap = nullptr;
}

