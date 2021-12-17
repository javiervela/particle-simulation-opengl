#ifndef CIRCLE2D_H
#define CIRCLE2D_H

#include "RegularPolygon2D.h"
#include "ApplConstants.h"

namespace shapes2d
{

    class Circle2D : public RegularPolygon2D
    {
        public:
        Circle2D(float x, float y, float rad, ColorIndex
                  fillColor, ColorIndex contourColor);
        
        virtual ~Circle2D(void);

        /**    Disabled default constructor
         */
        Circle2D(void) = delete;
        /**    Disabled copy constructor
         * @PARAM obj    object to copy
         */
        Circle2D(const Circle2D& obj) = delete;
        
        /**    Disabled move constructor
         * @PARAM obj    object to move
         */
        Circle2D(Circle2D&& obj) = delete;
        
        /**    Disabled copy operator
         * @PARAM obj    object to copy
         * @RETURN    reference to this object
         */
        const Circle2D& operator = (const Circle2D& obj) = delete;
        
        /**    Disabled move operator
         * @PARAM obj    object to move
         * @RETURN    reference to this object
         */
        Circle2D& operator = (Circle2D&& obj) = delete;

    };
}
#endif /* Circle2D_hpp */
