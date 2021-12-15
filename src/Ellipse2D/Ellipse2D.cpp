#include "Ellipse2D.h"

using namespace shapes2d;

Ellipse2D::Ellipse2D(float x, float y, float rad1, float rad2, float angle, ColorIndex
fillColor, ColorIndex contourColor)
    :   RegularPolygon2D(24, x, y, 1, fillColor, contourColor),
        rad1_(rad1),
        rad2_(rad2),
        angle_(angle)
{
}

Ellipse2D::~Ellipse2D(void)
{
    
}

void Ellipse2D::draw(void) const
{
    //--------------------------------------------------------
    //  1.  preserve the current reference frame
    //--------------------------------------------------------
    glPushMatrix();
    glRotatef(angle_, 0.f, 0.f, 1.f);
    glScalef(rad1_, rad2_, 1.f);
    
    RegularPolygon2D::draw();

    glPopMatrix();
    
}
