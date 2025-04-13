#ifndef WAVE_MAP_H
#define WAVE_MAP_H

class WaveMap {
public:
    WaveMap();
    WaveMap(unsigned int width, unsigned int height);

    void GetPositiveColor(
        unsigned char& positiveRed,
        unsigned char& positiveGreen,
        unsigned char& positiveBlue
    );
    void GetNeutralColor(
        unsigned char& neutralRed,
        unsigned char& neutralGreen,
        unsigned char& neutralBlue
    );
    void GetNegativeColor(
        unsigned char& negativeRed,
        unsigned char& negativeGreen,
        unsigned char& negativeBlue
    );
    double GetMaxAmplitude();

    void SetPositiveColor(
        unsigned char positiveRed,
        unsigned char positiveGreen,
        unsigned char positiveBlue
    );
    void SetNeutralColor(
        unsigned char neutralRed,
        unsigned char neutralGreen,
        unsigned char neutralBlue
    );
    void SetNegativeColor(
        unsigned char negativeRed,
        unsigned char negativeGreen,
        unsigned char negativeBlue
    );
    void SetMaxAmplitude(double maxAmplitude);

    void Update();
    unsigned char * ToColorMap();

    ~WaveMap();
private:
    unsigned int width;
    unsigned int height;

    double maxAmplitude;

    //Positive color (wave value at one)
    unsigned char positiveRed;
    unsigned char positiveGreen;
    unsigned char positiveBlue;

    //Neutral color (wave value at zero)
    unsigned char neutralRed;
    unsigned char neutralGreen;
    unsigned char neutralBlue;

    //Negative color (wave value at minus one)
    unsigned char negativeRed;
    unsigned char negativeGreen;
    unsigned char negativeBlue;

    //Matrix of wave at t=0 and t=-1
    double * waveMap;
    double * waveMapBefore;

    //Wave speed
    double waveSpeed;
};

#endif