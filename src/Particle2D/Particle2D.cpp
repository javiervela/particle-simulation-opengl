#include "Particle2D.h"
#include <cmath>

using namespace shapes2d;

Particle2D::Particle2D(float x, float y, float ax, float ay, float rad)
	: Circle2D(x, y, rad, kRED, kBLUE),
	  x_(x), y_(y), vx_(ax), vy_(y)
{
}

Particle2D::~Particle2D(void)
{
}

void Particle2D::draw(void)
{

	this->setFillColor(PARTICLE_PALETTE[pPrincipal]);
	this->setContourColor(PARTICLE_PALETTE[pPrincipal]);
	if (sqrt(pow(vx_, 2) + pow(vy_, 2)) > 1)
	{
		this->setFillColor(PARTICLE_PALETTE[pFast]);
		this->setContourColor(PARTICLE_PALETTE[pFast]);
	}
	else if (sqrt(pow(vx_, 2) + pow(vy_, 2)) > 0.5)
	{
		this->setFillColor(PARTICLE_PALETTE[pMedium]);
		this->setContourColor(PARTICLE_PALETTE[pMedium]);
	}

	Circle2D::draw();
}