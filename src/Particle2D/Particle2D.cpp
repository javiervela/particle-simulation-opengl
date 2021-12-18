#include "Particle2D.h"
#include <cmath>

using namespace shapes2d;

Particle2D::Particle2D(float x, float y, 
					   float ax, float ay, float rad, 
					   ColorIndex fillC, ColorIndex contourC,
					   ColorIndex primaryC, ColorIndex mediumC, ColorIndex fastC)
	: Circle2D(x, y, rad, fillC, contourC),
	  x_(x), y_(y), vx_(ax), vy_(y),
	  primary_(primaryC), 
	  medium_(mediumC),
	  fast_(fastC)
{
}

Particle2D::~Particle2D(void)
{
}

void Particle2D::draw(void)
{
	this->setFillColor(primary_);
	this->setContourColor(primary_);
	if (sqrt(pow(vx_, 2) + pow(vy_, 2)) > 1)
	{
		this->setFillColor(fast_);
		this->setContourColor(fast_);
	}
	else if (sqrt(pow(vx_, 2) + pow(vy_, 2)) > 0.5)
	{
		this->setFillColor(medium_);
		this->setContourColor(medium_);
	}

	Circle2D::draw();
}