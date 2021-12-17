#ifndef PARTICLE2D_H
#define PARTICLE2D_H

#include "ApplConstants.h"
#include "Circle2D.h"

namespace shapes2d
{

	class Particle2D : public Circle2D
	{
	public:
		Particle2D(float x, float y, float vx, float vy, float rad);

		virtual ~Particle2D(void);

		/**    Disabled default constructor
         */
		Particle2D(void) = delete;
		/**    Disabled copy constructor
         * @PARAM obj    object to copy
         */
		Particle2D(const Particle2D &obj) = delete;

		/**    Disabled move constructor
         * @PARAM obj    object to move
         */
		Particle2D(Particle2D &&obj) = delete;

		/**    Disabled copy operator
         * @PARAM obj    object to copy
         * @RETURN    reference to this object
         */
		const Particle2D &operator=(const Particle2D &obj) = delete;

		/**    Disabled move operator
         * @PARAM obj    object to move
         * @RETURN    reference to this object
         */
		Particle2D &operator=(Particle2D &&obj) = delete;

		void draw(void);

	private:
		float x_, y_, vx_, vy_;
	};

}
#endif
