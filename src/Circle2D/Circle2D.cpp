#include "Circle2D.h"

using namespace shapes2d;

Circle2D::Circle2D(float x, float y, float rad, ColorIndex
                     fillColor, ColorIndex contourColor)
:   Ellipse2D(x, y, rad, rad, 0.f, fillColor, contourColor)
{
}

Circle2D::~Circle2D(void)
{
    
}
