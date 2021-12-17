#include <cmath>
#include "Box2D.h"
#include "Square2D.h"

using namespace shapes2d;

Box2D::Box2D(float x, float y, float scale, ColorIndex fillColor,
			 ColorIndex contourColor)
	: Square2D(x, y, scale, fillColor, contourColor)
{
}

Box2D::~Box2D(void)
{
}

void Box2D::draw(void) const
{
	glPushMatrix();
	glRotatef(45, 0.f, 0.f, 1.f);
	Square2D::draw();
	glPopMatrix();
}