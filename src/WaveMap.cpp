#include "WaveMap.h"
#include "functions.h"

WaveMap::WaveMap(){
    width = 256; cmWidth = 254;
    height = 256; cmHeight = 254;

    deltaSpace = 1.0f;
    deltaTime = 1.0f;

    maxDispl = 1.0f;
    
    InitColors();
    InitDisplMaps();
    InitSpeedMap();
    InitIgnoreMap();
    InitColorMap();
}

WaveMap::WaveMap(MapDim width, MapDim height){
    this->width = width; this->cmWidth = width - 2;
    this->height = height; this->cmHeight = height - 2;

    deltaSpace = 1.0f;
    deltaTime = 1.0f;

    maxDispl = 1.0f;
    
    InitColors();
    InitDisplMaps();
    InitSpeedMap();
    InitIgnoreMap();
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

Displ WaveMap::GetMaxDispl(){ return maxDispl; }
Displ * WaveMap::GetDisplMap(){ return displMap; }
Displ * WaveMap::GetDisplMapBefore(){ return displMapBefore; }
Speed * WaveMap::GetSpeedMap(){ return speedMap; }
bool * WaveMap::GetIgnoreMap(){ return ignoreMap; }

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

Color * WaveMap::GetColorMap(){ return colorMap; }

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
void WaveMap::SetWaveSpeedValue(Speed waveSpeed){
    unsigned int nPoints = width * height;

    for(unsigned int i = 0; i < nPoints; i++){
        speedMap[i] = waveSpeed;
    }
}
void WaveMap::SetDeltaSpace(Distance deltaSpace){
    this->deltaSpace = deltaSpace;
}
void WaveMap::SetDeltaTime(DeltaT deltaTime){
    this->deltaTime = deltaTime;
}

void WaveMap::UpdateDisplMaps(){

    double timeSpaceFactor = deltaTime/deltaSpace;
    
    for(unsigned int i = 1; i < height - 1; i++){
        for(unsigned int j = 1; j < width - 1; j++){
            unsigned int currentPos = i * width + j;

            //Skip iteration if point is a ignore point
            if(ignoreMap[currentPos]){ continue; }

            Speed waveSpeed = speedMap[currentPos];

            Displ spaceContrib = displMap[currentPos - 1] + displMap[currentPos + 1]
                + displMap[currentPos - width] + displMap[currentPos + width] 
                - (4 * displMap[currentPos]);

            spaceContrib *= waveSpeed * waveSpeed * timeSpaceFactor;

            Displ displ = 2 * displMap[currentPos] - displMapBefore[currentPos] + spaceContrib;

            //Make sure values stay within -maxDispl and maxDispl
            if (displ > maxDispl) {displ = maxDispl;}
            else if (displ < -maxDispl) {displ = -maxDispl;}

            displMapBefore[currentPos] = displ;
        }
    }

    Displ * temp = displMapBefore;
    displMapBefore = displMap;
    displMap = temp;
}

void WaveMap::UpdateColorMap(){
    for(unsigned int i = 0; i < cmHeight; i++){
        unsigned int waveStart = width * (i + 1) + 1;
        for(unsigned int j = 0; j < cmWidth; j++){
            unsigned int currentPos = waveStart + j;

            if(ignoreMap[currentPos]){ continue; }

            Displ displ = displMap[currentPos];
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
    displMap[y * width + x] = displ;
}
void WaveMap::PokeMapBefore(Coor x, Coor y, Displ displ){
    displMapBefore[y * width + x] = displ;
}
void WaveMap::EnableIgnorePoint(Coor x, Coor y){
    ignoreMap[y * width + x] = true;
}
void WaveMap::DisableIgnorePoint(Coor x, Coor y){
    ignoreMap[y * width + x] = false;
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

void WaveMap::InitDisplMaps(){
    unsigned int nPoints = width * height;

    displMap = new Displ[nPoints];
    displMapBefore = new Displ[nPoints];

    for(unsigned int i = 0; i < nPoints; i++){
        displMap[i] = 0.0f;
        displMapBefore[i] = 0.0f;
    }
}

void WaveMap::InitSpeedMap(){
    unsigned int nPoints = width * height;

    speedMap = new Speed[nPoints];

    for(unsigned int i = 0; i < nPoints; i++){
        speedMap[i] = 1.0f;
    }
}

void WaveMap::InitIgnoreMap(){
    unsigned int nPoints = width * height;

    ignoreMap = new bool[nPoints];

    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            ignoreMap[i * width + j] = i == 0 || i == (height - 1) || j == 0 || j == (width - 1); 
        }
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
    delete[] displMap;
    delete[] displMapBefore;
    delete[] speedMap;
    delete[] ignoreMap;
    delete[] colorMap;
    
    displMap = nullptr;
    displMapBefore = nullptr;
    speedMap = nullptr;
    ignoreMap = nullptr;
    colorMap = nullptr;
}

