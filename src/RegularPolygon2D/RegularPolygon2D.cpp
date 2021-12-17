#include<cmath>

#include "RegularPolygon2D.h"
#include "ApplConstants.h"

using namespace shapes2d;

unsigned int RegularPolygon2D::counter_ = 0;

RegularPolygon2D::RegularPolygon2D(int n, float x, float y, float scale, ColorIndex
	fillColor, ColorIndex contourColor)
	:	GraphicObject2D(),
        n_(n),
		x_(x),
		y_(y),
		scale_(scale),
		fillColor_(fillColor),
		contourColor_(contourColor),
		index_(counter_++)
{
}


RegularPolygon2D::~RegularPolygon2D(void) 
{
}

//
// public methods
//

void RegularPolygon2D::draw(void) const
{
	//--------------------------------------------------------
   //  1.  preserve the current reference frame
   //--------------------------------------------------------
	glPushMatrix();

	//--------------------------------------------------------
	//  2.  apply transformation between reference frames
	//--------------------------------------------------------
	glTranslatef(x_, y_, 0.f);
	glRotatef(45.f, 0.f, 0.f, 1.f);
	glScalef(scale_, scale_, 1.f);


	//--------------------------------------------------------
	//  3.  draw the polygon
	//--------------------------------------------------------

	// set the color
	glColor4f(COLOR[fillColor_][0], COLOR[fillColor_][1], COLOR[fillColor_][2],
		COLOR[fillColor_][3]);

	//get the angle for each vertex
	float pi = 3.14159265;
	float angle = 360 / n_;
	float angleToRad = angle * (pi / 180);

	// draw the polygon
	glBegin(GL_POLYGON);
	// build the polygon using the angle to plot the vertices inside a circle
	for (float i = n_; i > 0; i--)
	{
		glVertex2f(cos(angleToRad * i), sin(angleToRad * i));
	}
	glEnd();

	// set the color
	glColor4f(COLOR[contourColor_][0], COLOR[contourColor_][1], COLOR[contourColor_][2],
		COLOR[contourColor_][3]);


	// draw the outline
	glBegin(GL_LINE_LOOP);
	// build the polygon using the angle to plot the vertices inside a circle
	for (float i = n_; i > 0; i--)
	{
		glVertex2f(cos(angleToRad * i), sin(angleToRad * i));
	}
	glEnd();

	//--------------------------------------------------------
	//  4.  restore the previous reference frame
	//--------------------------------------------------------
	glPopMatrix();

}


unsigned int RegularPolygon2D::getIndex(void) const
{
	return index_;
}
