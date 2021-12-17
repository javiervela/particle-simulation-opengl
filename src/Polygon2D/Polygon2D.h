/**
 * @file Polygon2D.h
 * @author Javier Vela
 * @brief Header file for Polygon 2 D object
 * @date 2021-10-12
 */

#ifndef POLYGON2D_H
#define POLYGON2D_H

#include <vector>
#include <utility>
#include "glPlatform.h"
#include "ApplConstants.h"
#include "GraphicObject2D.h"

namespace shapes2d
{
    class Polygon2D : public GraphicObject2D
    {
    public:
        // Constructors

        /**
         * @brief Construct a new Polygon 2 D object
         * 
         * @param n number of sides
         * @param x array of X coordinates of vertices
         * @param y array of Y coordinates of vertices
         * @param fillColor inside color
         * @param contourColor border color
         */
        Polygon2D(int n, const float *x, const float *y,
                  ColorIndex fillColor, ColorIndex contourColor);

        /**
         * @brief Construct a new Polygon 2 D object
         * 
         * @param n number of sides
         * @param originX x coordinate origin
         * @param originY x coordinate origin
         * @param x array of X coordinates of vertices relative to origin
         * @param y array of Y coordinates of vertices relative to origin
         * @param fillColor inside color
         * @param contourColor border color
         */
        Polygon2D(int n, float originX, float originY,
                  const float *x, const float *y, ColorIndex fillColor,
                  ColorIndex contourColor);

        /**
         * @brief Construct a new Polygon 2 D object
         * 
         * @param vx vector of X coordinates of vertices
         * @param vy vector of Y coordinates of vertices
         * @param fillColor inside color
         * @param contourColor border color
         */
        Polygon2D(const std::vector<float> &vx, const std::vector<float> &vy,
                  ColorIndex fillColor, ColorIndex contourColor);

        /**
         * @brief Construct a new Polygon 2 D object
         * 
         * @param vxy vector of pairs of X and Y coordinates of vertices
         * @param fillColor inside color
         * @param contourColor border color
         */
        Polygon2D(const std::vector<std::pair<float, float>> &vxy,
                  ColorIndex fillColor, ColorIndex contourColor);

        // Destructor

        /**
         * @brief Destroy the Polygon 2 D object
         * 
         */
        virtual ~Polygon2D(void);

        // Deleted constructors and operators

        Polygon2D(void) = delete;
        Polygon2D(const Polygon2D &reg) = delete;
        Polygon2D(Polygon2D &&reg) = delete;
        Polygon2D &operator=(const Polygon2D &reg) = delete;
        Polygon2D &operator=(Polygon2D &&reg) = delete;

        // Getters

        /**
         * @brief Get the n_ attribute
         * 
         * @return int 
         */
        inline int getN() const
        {
            return n_;
        }

        /**
         * @brief Get the x_ attribute
         * 
         * @return float 
         */
        inline float getX() const
        {
            return x_;
        }

        /**
         * @brief Get the y_ attribute
         * 
         * @return float 
         */
        inline float getY() const
        {
            return y_;
        }

        /**
         * @brief Get the fillColor_ attribute
         * 
         * @return ColorIndex 
         */
        inline ColorIndex getFillColor() const
        {
            return fillColor_;
        }

        /**
         * @brief Get the contourColor_ attribute
         * 
         * @return ColorIndex 
         */
        inline ColorIndex getContourColor() const
        {
            return contourColor_;
        }

        /**
         * @brief Get the coordinates_ attribute
         * 
         * @return std::vector<std::pair<float, float>> 
         */
        inline std::vector<std::pair<float, float>> getCoordinates() const
        {
            return coordinates_;
        }

        // Public methods

        /**
         * @brief Draw the Polygon 2 D object
         * 
         */
        void draw(void) const;

    private:
        // Attributes

        /// Number of vertices
        int n_;
        /// Center coordinates X Y
        float x_, y_;
        /// Inside and border color
        ColorIndex fillColor_, contourColor_;
        /// Vector of X and Y coordinates
        std::vector<std::pair<float, float>> coordinates_;
    };
}

#endif