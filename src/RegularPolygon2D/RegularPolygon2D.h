#ifndef REGULARPOLYGON2D
#define REGULARPOLYGON2D

#include "glPlatform.h"
#include "ApplConstants.h"
#include "GraphicObject2D.h"

//----------------------------------------------------------------------------------
//-----------------------------------Class definition-------------------------------
//

namespace shapes2d
{
    class RegularPolygon2D : public GraphicObject2D {
			//
			// Constructors and deconstructors
			//
	public:
		RegularPolygon2D(int n, float x, float y, float scale, ColorIndex
			fillColor, ColorIndex contourColor);
	
		virtual ~RegularPolygon2D(void);

		//
		// public methods
		//

		virtual void draw(void) const;

		virtual unsigned int getIndex(void) const;
		
		// "pure virtual" function (abstrasct method in Java)
//		virtual float getArea(void) const = 0;
		
		
		// getters and setters
		
		inline float getScale(void) const {
			return scale_;
		}


		inline float getX(void) const {
			return x_;
		}
		inline float getY(void) const {
			return y_;
		}
		inline void setX(float x) {
			x_ = x;
		}
		inline void setY(float y) {
			y_ = y;
		}

        /**    Disabled default constructor
         */
        RegularPolygon2D(void) = delete;
        /**    Disabled copy constructor
         * @PARAM obj    object to copy
         */
        RegularPolygon2D(const RegularPolygon2D& obj) = delete;
        
        /**    Disabled move constructor
         * @PARAM obj    object to move
         */
        RegularPolygon2D(RegularPolygon2D&& obj) = delete;
        
        /**    Disabled copy operator
         * @PARAM obj    object to copy
         * @RETURN    reference to this object
         */
        const RegularPolygon2D& operator = (const RegularPolygon2D& obj) = delete;
        
        /**    Disabled move operator
         * @PARAM obj    object to move
         * @RETURN    reference to this object
         */
        RegularPolygon2D& operator = (RegularPolygon2D&& obj) = delete;
        

	private:
		//
		// private variables
		//
		int n_;
		float x_, y_, scale_;
		ColorIndex fillColor_, contourColor_;

		unsigned int index_;
		static unsigned int counter_;

	};
	

}



#endif
