#include "Circle2D.h"

using namespace shapes2d;

Circle2D::Circle2D(float x, float y, float rad, ColorIndex fillColor, ColorIndex contourColor)
    : RegularPolygon2D(24, x, y, rad, fillColor, contourColor)
{
}

Circle2D::~Circle2D(void)
{
}
