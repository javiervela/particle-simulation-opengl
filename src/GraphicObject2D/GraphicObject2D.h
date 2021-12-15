#ifndef GRAPHICOBJECT2D_H
#define GRAPHICOBJECT2D_H

namespace shapes2d {
   
    class GraphicObject2D {
        
    
    public:
    
        virtual ~GraphicObject2D(void);

        virtual void draw(void) const = 0;
    
    
        /**    Disabled copy constructor
         * @PARAM obj    object to copy
         */
        GraphicObject2D(const GraphicObject2D& obj) = delete;
    
        /**    Disabled move constructor
         * @PARAM obj    object to move
         */
        GraphicObject2D(GraphicObject2D&& obj) = delete;
    
        /**    Disabled copy operator
         * @PARAM obj    object to copy
         * @RETURN    reference to this object
         */
        const GraphicObject2D& operator = (const GraphicObject2D& obj) = delete;
    
        /**    Disabled move operator
         * @PARAM obj    object to move
         * @RETURN    reference to this object
         */
        GraphicObject2D& operator = (GraphicObject2D&& obj) = delete;

protected:
    /**     default constructor
     */
    GraphicObject2D(void);
    };
}
#endif /* GraphicObject2D_hpp */
