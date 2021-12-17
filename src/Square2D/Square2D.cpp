#include <cmath>
#include "Square2D.h"

using namespace shapes2d;

Square2D::Square2D(float x, float y, float scale, ColorIndex fillColor,
                   ColorIndex contourColor)
    : RegularPolygon2D(n_, x, y, scale, fillColor, contourColor)
{
}

Square2D::~Square2D(void)
{
}
