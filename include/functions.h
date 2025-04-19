#include "types.h"

inline void interpolateColors(
    ColorCoor leftRed, ColorCoor leftGreen, ColorCoor leftBlue,
    ColorCoor rightRed, ColorCoor rightGreen, ColorCoor rightBlue,
    ColorCoor& interRed, ColorCoor& interGreen, ColorCoor& interBlue,
    double factor
){
    interRed = static_cast<ColorCoor>((rightRed - leftRed) * factor) + leftRed;
    interGreen = static_cast<ColorCoor>((rightGreen - leftGreen) * factor) + leftGreen;
    interBlue = static_cast<ColorCoor>((rightBlue - leftBlue) * factor) + leftBlue;
}

inline double euclideanSquared(
    Coor x1, Coor y1, Coor x2, Coor y2
){
    Distance dX = x2 - x1; Distance dY = y2 - y1;
    return dX * dX + dY * dY; 
}