/**
 * @file RegularPolygon2D.h
 * @author Javier Vela
 * @brief Header file for Regular Polygon 2 D object
 * @date 2021-10-12
 */

#ifndef REGULAR_POLYGON2D_H
#define REGULAR_POLYGON2D_H

#include <vector>
#include <utility>
#include "glPlatform.h"
#include "ApplConstants.h"
#include "Polygon2D.h"

namespace shapes2d
{
    class RegularPolygon2D : public Polygon2D
    {
    public:
        // Constructor

        /**
         * @brief Construct a new Regular Polygon 2 D object
         * 
         * @param n number of sides
         * @param x x coordinate origin
         * @param y y coordinate origin
         * @param scale radius
         * @param fillColor inside color
         * @param contourColor border color
         */
        RegularPolygon2D(int n, float x, float y, float scale, ColorIndex fillColor, ColorIndex contourColor);

        // Destructor

        /**
         * @brief Destroy the Regular Polygon 2 D object
         * 
         */
        virtual ~RegularPolygon2D(void);

        // Deleted constructors and operators

        RegularPolygon2D(void) = delete;
        RegularPolygon2D(const RegularPolygon2D &reg) = delete;
        RegularPolygon2D(RegularPolygon2D &&reg) = delete;
        RegularPolygon2D &operator=(const RegularPolygon2D &reg) = delete;
        RegularPolygon2D &operator=(RegularPolygon2D &&reg) = delete;

        // Getters

        /**
         * @brief Get the scale_ attribute
         * 
         * @return float 
         */
        inline float getScale() const
        {
            return scale_;
        }

    private:
        // Attributes

        /// Radius
        float scale_;

        // Private methods

        /**
         * @brief Calculate vector of pair X Y coordinates of the Regular Polygon 2 D object
         * 
         * @param n number of sides
         * @param x x coordinate origin
         * @param y y coordinate origin
         * @param scale radius
         * @return std::vector<std::pair<float, float>> 
         */
        std::vector<std::pair<float, float>> calculateCoordinates(int n, float x, float y, float scale) const;
    };
}

#endif