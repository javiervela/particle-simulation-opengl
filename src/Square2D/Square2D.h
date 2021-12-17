/**
 * @file Square2D.h
 * @author Javier Vela
 * @brief Header file for Square 2 D object
 * @date 2021-10-12
 */

#ifndef SQUARE2D_H
#define SQUARE2D_H

#include <vector>
#include <utility>
#include "glPlatform.h"
#include "ApplConstants.h"
#include "RegularPolygon2D.h"

namespace shapes2d
{
	class Square2D : public RegularPolygon2D
	{
	public:
		// Constructor

		/**
		 * @brief Construct a new Square 2 D object
		 *
		 * @param x x coordinate origin
		 * @param y y coordinate origin
		 * @param scale width and height
		 * @param fillColor inside color
		 * @param contourColor border color
		 */
		Square2D(float x, float y, float scale, ColorIndex fillColor, ColorIndex contourColor);

		// Destructor

		/**
		 * @brief Destroy the Square 2 D object
		 *
		 */
		~Square2D(void);

		// Deleted constructors and operators

		Square2D(void) = delete;
		Square2D(const Square2D &sqr) = delete;
		Square2D(Square2D &&sqr) = delete;
		Square2D &operator=(const Square2D &sqr) = delete;
		Square2D &operator=(Square2D &&sqr) = delete;

	private:
		// Attributes

		/// Number of vertices
		static const int n_ = 4;
	};
}

#endif