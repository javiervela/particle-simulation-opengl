/**
 * @file RegularPolygon2D.cpp
 * @author Javier Vela
 * @brief Source file for Regular Polygon 2 D object 
 * @date 2021-10-12
 */

#include <cmath>
#include "RegularPolygon2D.h"

using namespace shapes2d;

RegularPolygon2D::RegularPolygon2D(int n, float x, float y, float scale,
                                   ColorIndex fillColor, ColorIndex contourColor)
    : Polygon2D(calculateCoordinates(n, x, y, scale), fillColor, contourColor),
      scale_(scale)
{
}

RegularPolygon2D::~RegularPolygon2D(void)
{
}

std::vector<std::pair<float, float>> RegularPolygon2D::calculateCoordinates(int n, float x, float y, float scale) const
{
    // Radius (distance to vertices)
    const float radius = scale;

    // Calculate coordinates
    std::vector<std::pair<float, float>> coordinates;
    coordinates.clear();
    for (int i = 0; i < n; i++)
    {
        float angle = static_cast<float>(i) / static_cast<float>(n) * 2 * M_PI;
        // X coordinate -> cos, with origin offset
        float x_coordinate = cos(angle) * radius + x;
        // Y coordinate -> sin, with origin offset
        float y_coordinate = sin(angle) * radius + y;

        coordinates.push_back(std::pair<float, float>(x_coordinate, y_coordinate));
    }

    return coordinates;
}