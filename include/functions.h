#include "types.h"

inline void interpolateColors(
    Color leftRed, Color leftGreen, Color leftBlue,
    Color rightRed, Color rightGreen, Color rightBlue,
    Color& interRed, Color& interGreen, Color& interBlue,
    double factor
){
    interRed = static_cast<Color>((rightRed - leftRed) * factor) + leftRed;
    interGreen = static_cast<Color>((rightGreen - leftGreen) * factor) + leftGreen;
    interBlue = static_cast<Color>((rightBlue - leftBlue) * factor) + leftBlue;
}