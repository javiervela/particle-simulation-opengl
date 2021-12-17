/**
 * @file Box2D.h
 * @author Javier Vela
 * @brief Header file for Box 2 D object
 * @date 2021-10-12
 */

#ifndef BOX2D_H
#define BOX2D_H

#include <vector>
#include <utility>
#include "glPlatform.h"
#include "ApplConstants.h"
#include "Square2D.h"

namespace shapes2d
{
	class Box2D : public Square2D
	{
	public:
		// Constructor

		/**
		 * @brief Construct a new Box 2 D object
		 *
		 * @param x x coordinate origin
		 * @param y y coordinate origin
		 * @param scale width and height
		 * @param fillColor inside color
		 * @param contourColor border color
		 */
		Box2D(float x, float y, float scale, ColorIndex fillColor, ColorIndex contourColor);

		// Destructor

		/**
		 * @brief Destroy the Box 2 D object
		 *
		 */
		~Box2D(void);

		// Deleted constructors and operators

		Box2D(void) = delete;
		Box2D(const Box2D &sqr) = delete;
		Box2D(Box2D &&sqr) = delete;
		Box2D &operator=(const Box2D &sqr) = delete;
		Box2D &operator=(Box2D &&sqr) = delete;

		void draw(void) const;

	private:
		// Attributes

		/// Number of vertices
		static const int n_ = 4;
	};
}

#endif