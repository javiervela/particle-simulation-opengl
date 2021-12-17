/**
 * @file Polygon2D.cpp
 * @author Javier Vela
 * @brief Source file for Polygon 2 D object 
 * @date 2021-10-12
 */

#include "Polygon2D.h"

using namespace shapes2d;

Polygon2D::Polygon2D(int n, const float *x, const float *y,
                     ColorIndex fillColor, ColorIndex contourColor)
    : n_(n),
      x_(0.f),
      y_(0.f),
      fillColor_(fillColor),
      contourColor_(contourColor)
{
    coordinates_.clear();
    for (int i = 0; i < n_; i++)
    {
        coordinates_.push_back(std::pair<float, float>(x[i], y[i]));
    }
}

Polygon2D::Polygon2D(int n, float originX, float originY,
                     const float *x, const float *y, ColorIndex fillColor,
                     ColorIndex contourColor)
    : n_(n),
      x_(originX),
      y_(originY),
      fillColor_(fillColor),
      contourColor_(contourColor)
{
    coordinates_.clear();
    for (int i = 0; i < n_; i++)
    {
        coordinates_.push_back(std::pair<float, float>(x[i], y[i]));
    }
}

Polygon2D::Polygon2D(const std::vector<float> &vx, const std::vector<float> &vy,
                     ColorIndex fillColor, ColorIndex contourColor)
    : n_(vx.size()),
      x_(0.f),
      y_(0.f),
      fillColor_(fillColor),
      contourColor_(contourColor)
{
    coordinates_.clear();
    for (int i = 0; i < n_; i++)
    {
        coordinates_.push_back(std::pair<float, float>(vx.at(i), vy.at(i)));
    }
}

Polygon2D::Polygon2D(const std::vector<std::pair<float, float>> &vxy,
                     ColorIndex fillColor, ColorIndex contourColor)
    : n_(vxy.size()),
      x_(0.f),
      y_(0.f),
      fillColor_(fillColor),
      contourColor_(contourColor),
      coordinates_(vxy)
{
}

Polygon2D::~Polygon2D(void)
{
}

void Polygon2D::draw(void) const
{
    glPushMatrix();

    /// Translate to center
    glTranslatef(x_, y_, 0.f);

    /// Draw polygon
    glColor4f(COLOR[fillColor_][0], COLOR[fillColor_][1], COLOR[fillColor_][2], COLOR[fillColor_][3]);
    glBegin(GL_POLYGON);
    for (std::pair<float, float> xy : coordinates_)
    {
        glVertex2f(xy.first, xy.second);
    }
    glEnd();

    /// Draw contour
    glColor4f(COLOR[contourColor_][0], COLOR[contourColor_][1], COLOR[contourColor_][2], COLOR[contourColor_][3]);
    glBegin(GL_LINE_LOOP);
    for (std::pair<float, float> xy : coordinates_)
    {
        glVertex2f(xy.first, xy.second);
    }
    glEnd();

    glPopMatrix();
}
