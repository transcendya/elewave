#include "WaveMap.h"

WaveMap::WaveMap(){
    width = 256;
    height = 256;

    waveSpeed = 1.0f;
    maxDispl = 1.0f;
    
    InitColors();
    InitWaveMaps();
}

WaveMap::WaveMap(MapDim width, MapDim height){
    this->width = width;
    this->height = height;

    waveSpeed = 1.0f;
    maxDispl = 1.0f;
    
    InitColors();
    InitWaveMaps();
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

void WaveMap::SetPositiveColor(
    Color positiveRed, Color positiveGreen, Color positiveBlue
){
    this->positiveRed = positiveRed;
    this->positiveGreen = positiveGreen;
    this->positiveBlue = positiveBlue;
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

void WaveMap::Update(){
    unsigned int nPoints = width * height;

    spaceFactor = (waveSpeed * waveSpeed * deltaTime)/deltaSpace;

    
    for(unsigned int i = 1; i < height - 1; i++){
        for(unsigned int j = 1; j < width - 1; j++){
            unsigned int currentPos = i * width + j;

            spaceContrib = waveMap[currentPos - 1] + waveMap[currentPos + 1]
                + waveMap[currentPos - width] + waveMap[currentPos + width] 
                - (4 * waveMap[currentPos]);

            spaceContrib *= spaceFactor;

            timeContrib = 2 * waveMap[currentPos] - waveMapBefore[currentPos];

            waveMapBefore[currentPos] = timeContrib + spaceContrib;
        }
    }

    Displ * temp = waveMapBefore;
    waveMapBefore = waveMap;
    waveMap = waveMapBefore;
}

Color * WaveMap::ToColorMap(){
    //TO DO
    return nullptr;
}

void WaveMap::InitColors(){
    //By default, positive is red
    positiveRed = 255;
    positiveGreen = 0;
    positiveBlue = 0;
    
    //By default, neutral is white
    positiveRed = 255;
    positiveGreen = 255;
    positiveBlue = 255;

    //By default, negative is blue
    positiveRed = 0;
    positiveGreen = 0;
    positiveBlue = 255;
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

WaveMap::~WaveMap(){
    delete[] waveMap;
    delete[] waveMapBefore;
    
    waveMap = nullptr;
    waveMapBefore = nullptr;
}

