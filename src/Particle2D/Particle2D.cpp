#include "Particle2D.h"

using namespace shapes2d;

Particle2D::Particle2D(float x, float y, float rad)
	: Circle2D(x, y, rad, kRED, kBLUE)
{
}

Particle2D::~Particle2D(void)
{
}

void Particle2D::draw(void)
{
	this->setFillColor(kWHITE);
	this->setContourColor(kWHITE);

	Circle2D::draw();
}