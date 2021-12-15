#ifndef ELLIPSE2D_H
#define ELLIPSE2D_H

#include "RegularPolygon2D.h"

namespace shapes2d
{
    class Ellipse2D : public RegularPolygon2D {
        //
        // Constructors and deconstructors
        //
    public:
        Ellipse2D(float x, float y, float rad1, float rad2, float angle, ColorIndex
                         fillColor, ColorIndex contourColor);
        
        virtual ~Ellipse2D(void);
        
        //
        // public methods
        //
        void draw(void) const;
 
        /**    Disabled default constructor
         */
        Ellipse2D(void) = delete;
        /**    Disabled copy constructor
         * @PARAM obj    object to copy
         */
        Ellipse2D(const Ellipse2D& obj) = delete;
        
        /**    Disabled move constructor
         * @PARAM obj    object to move
         */
        Ellipse2D(Ellipse2D&& obj) = delete;
        
        /**    Disabled copy operator
         * @PARAM obj    object to copy
         * @RETURN    reference to this object
         */
        const Ellipse2D& operator = (const Ellipse2D& obj) = delete;
        
        /**    Disabled move operator
         * @PARAM obj    object to move
         * @RETURN    reference to this object
         */
        Ellipse2D& operator = (Ellipse2D&& obj) = delete;

        
    private:
        //
        // private variables
        //
        float rad1_, rad2_;
        float angle_;
        
    };
    
    
}

#endif /* Ellipse2D_hpp */
